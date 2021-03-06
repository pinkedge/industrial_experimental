﻿/*
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2015, Southwest Research Institute
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 	* Redistributions of source code must retain the above copyright
 * 	notice, this list of conditions and the following disclaimer.
 * 	* Redistributions in binary form must reproduce the above copyright
 * 	notice, this list of conditions and the following disclaimer in the
 * 	documentation and/or other materials provided with the distribution.
 * 	* Neither the name of the Southwest Research Institute, nor the names
 *	of its contributors may be used to endorse or promote products derived
 *	from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FLATHEADERS
#include "simple_message/messages/dynamic_group_status_message.h"
#include "simple_message/joint_data.h"
#include "simple_message/byte_array.h"
#include "simple_message/log_wrapper.h"
#else
#include "dynamic_group_status_message.h"
#include "joint_data.h"
#include "byte_array.h"
#include "log_wrapper.h"
#endif

using namespace industrial::shared_types;
using namespace industrial::byte_array;
using namespace industrial::simple_message;
using namespace industrial::dynamic_group_status;

namespace industrial
{
namespace dynamic_group_status_message
{

DynamicGroupStatusMessage::DynamicGroupStatusMessage(void)
{
  this->init();
}

DynamicGroupStatusMessage::~DynamicGroupStatusMessage(void)
{

}

bool DynamicGroupStatusMessage::init(SimpleMessage & msg)
{
  bool rtn = false;
  ByteArray data = msg.getData();
  this->init();

  if (this->status_.unloadFront(&data))
  {
    rtn = true;
  }
  else
  {
    LOG_ERROR("Failed to unload dynamic group status data");
  }
  return rtn;
}

void DynamicGroupStatusMessage::init(DynamicGroupStatus & status)
{
  this->init();
  this->status_ = status;
}

void DynamicGroupStatusMessage::init()
{
  this->setMessageType(StandardMsgTypes::DYNAMIC_GROUP_STATUS);
  this->status_.init();
}


bool DynamicGroupStatusMessage::load(ByteArray *buffer)
{
  bool rtn = false;
  LOG_COMM("Executing dynamic group status message load");
  if (buffer->load(this->status_))
  {
    rtn = true;
  }
  else
  {
    rtn = false;
    LOG_ERROR("Failed to load dynamic group status data");
  }
  return rtn;
}

bool DynamicGroupStatusMessage::unload(ByteArray *buffer)
{
  LOG_ERROR("DynamicGroupStatusMessage.unload() unsupported.  Use unloadFront() instead.");
  return false;
}

bool DynamicGroupStatusMessage::unloadFront(ByteArray *buffer)
{
  bool rtn = false;
  LOG_COMM("Executing dynamic group status message unload");

  if (this->status_.unloadFront(buffer))
  {
    rtn = true;
  }
  else
  {
    rtn = false;
    LOG_ERROR("Failed to unload dynamic group status data");
  }
  return rtn;
}

}
}

