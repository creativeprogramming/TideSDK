/*
 * Copyright (c) 2010 Appcelerator, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TCPServerConnection_h
#define TCPServerConnection_h

#include <queue>

#include <tide/tide.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketAcceptor.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/NObserver.h>
#include <Poco/RunnableAdapter.h>
#include <Poco/Thread.h>

namespace ti {

class TCPServerConnection : public StaticBoundObject {
public:
    TCPServerConnection(Poco::Net::StreamSocket& s, Poco::Net::SocketReactor & reactor_);
    virtual ~TCPServerConnection();

private:
    enum {
        BUFFER_SIZE = 1024
    };

    void onReadable (const Poco::AutoPtr<Poco::Net::ReadableNotification>&);
    void onShutdown (const Poco::AutoPtr<Poco::Net::ShutdownNotification>&);
    void onWritable (const Poco::AutoPtr<Poco::Net::WritableNotification>&);
    void onErrored(const Poco::AutoPtr<Poco::Net::ErrorNotification>&);

    void Write(const ValueList& args, ValueRef result);
    void Close(const ValueList& args, ValueRef result);
    void IsClosed(const ValueList& args, ValueRef result);
    void SetOnRead(const ValueList& args, ValueRef result);
    void SetOnWrite(const ValueList& args, ValueRef result);
    void SetOnError(const ValueList& args, ValueRef result);
    void SetOnReadComplete(const ValueList& args, ValueRef result);

    Poco::Net::StreamSocket socket;
    Poco::Net::SocketReactor& reactor;
    bool closed;
    MethodRef onRead;
    MethodRef onWrite;
    MethodRef onError;
    MethodRef onReadComplete;
    std::queue<BytesRef> sendData;
    Poco::Mutex sendDataMutex;
    size_t currentSendDataOffset;
    bool readStarted;
    bool writeReadyHandlerInstalled;
};
    
} // namespace ti

#endif