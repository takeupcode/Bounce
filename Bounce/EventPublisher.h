//
//  EventPublisher.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/24/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "EventSubscriber.h"

template <typename... Args>
class EventPublisher
{
public:
    typedef EventPublisher<Args...> PublisherType;
    typedef EventSubscriber<Args...> SubscriberType;
    typedef std::weak_ptr<SubscriberType> WeakSubscriberType;
    typedef std::shared_ptr<SubscriberType> SharedSubscriberType;
    
private:
    typedef std::map<std::string, WeakSubscriberType> MappedWeakSubscriberType;
    
    struct EventPublisherData
    {
        std::unique_ptr<MappedWeakSubscriberType> mSubscribers;
    };
    
public:
    EventPublisher ()
    : mData(new EventPublisherData())
    {
        mData->mSubscribers.reset(new MappedWeakSubscriberType());
    }
    
    EventPublisher (PublisherType && src)
    : mData(src.mData.release())
    { }
    
    virtual ~EventPublisher ()
    { }
    
    void swap (PublisherType & other)
    {
        std::unique_ptr<EventPublisherData> thisData(mData.release());
        std::unique_ptr<EventPublisherData> otherData(other.mData.release());
        
        mData.reset(otherData.release());
        other.mData.reset(thisData.release());
    }
    
    PublisherType & operator = (PublisherType && rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        
        mData.reset(rhs.mData.release());
        
        return *this;
    }
    
    void signal (Args... args) const
    {
        std::vector<std::string> badConnectionIdentities;
        
        for (auto & identifiedSubscriberPair : *mData->mSubscribers.get())
        {
            try
            {
                SharedSubscriberType sharedSubscriber(identifiedSubscriberPair.second);
                
                sharedSubscriber->notify(args...);
            }
            catch (const std::bad_weak_ptr &)
            {
                badConnectionIdentities.push_back(identifiedSubscriberPair.first);
            }
        }
        for (auto & identity : badConnectionIdentities)
        {
            mData->mSubscribers->erase(identity);
        }
    }
    
    void connect (const std::string & identity, const SharedSubscriberType & subscriber)
    {
        WeakSubscriberType weakSubscriber = subscriber;
        
        auto identifiedPosition = mData->mSubscribers->find(identity);
        if (identifiedPosition != mData->mSubscribers->end())
        {
            identifiedPosition->second = weakSubscriber;
        }
        else
        {
            mData->mSubscribers->insert({identity, weakSubscriber});
        }
    }
    
    void disconnect (const std::string & identity)
    {
        mData->mSubscribers->erase(identity);
    }
    
private:
    EventPublisher (const PublisherType & src) = delete;
    PublisherType & operator = (const PublisherType & rhs) = delete;
    
    std::unique_ptr<EventPublisherData> mData;
};

