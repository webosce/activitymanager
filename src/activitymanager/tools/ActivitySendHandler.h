// Copyright (c) 2017-2020 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef __ACTIVITY_SEND_HANDLER_H__
#define __ACTIVITY_SEND_HANDLER_H__

#include <glib.h>
#include <string>

class ActivitySendHandler {
public:
    static ActivitySendHandler& getInstance()
    {
        static ActivitySendHandler _instance;
        return _instance;
    }

    static gboolean onRead(GIOChannel* channel, GIOCondition condition, gpointer data);

    void initialize();

private:
    ActivitySendHandler();
    ~ActivitySendHandler();
    ActivitySendHandler(const ActivitySendHandler& copy);
    ActivitySendHandler& operator=(const ActivitySendHandler& copy);

    int m_pipeReq;
    int m_pipeResp;
    std::string m_ipcDir;
    std::string m_reqPipePath;
    std::string m_respPipePath;
};

#endif /* __ACTIVITY_SEND_HANDLER_H__ */
