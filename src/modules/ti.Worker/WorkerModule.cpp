/*
 * Copyright (c) 2009-2010 Appcelerator, Inc. All Rights Reserved.
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

#include "WorkerModule.h"

#include <tide/tide.h>

#include "WorkerBinding.h"

namespace ti {

TIDE_MODULE(WorkerModule, STRING(MODULE_NAME), STRING(MODULE_VERSION));

void WorkerModule::Initialize()
{
    GlobalObject::GetInstance()->SetObject("Worker", new WorkerBinding());
}

void WorkerModule::Stop()
{
    GlobalObject::GetInstance()->SetNull("Worker");
}

} // namespace ti