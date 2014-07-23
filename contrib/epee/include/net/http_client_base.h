// Copyright (c) 2014, The Monero Project
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Parts of this file are originally copyright (c) 2006-2013, Andrey N. Sabelnikov

#pragma once 

namespace epee
{
  namespace net_utils
  {
    struct i_sub_handler
    {
      virtual ~i_sub_handler(){}

      virtual bool update_in( std::string& piece_of_transfer)=0;
      virtual void stop(std::string& OUT collect_remains)=0;
      virtual bool update_and_stop(std::string& OUT collect_remains, bool& is_changed)
      {
        is_changed = true;
        bool res = this->update_in(collect_remains);
        if(res)
          this->stop(collect_remains);
        return res;
      }
    };


    struct i_target_handler
    {
      virtual ~i_target_handler(){}
      virtual bool handle_target_data( std::string& piece_of_transfer)=0;
    };


    class do_nothing_sub_handler: public i_sub_handler
    {
    public: 
      do_nothing_sub_handler(i_target_handler* powner_filter):m_powner_filter(powner_filter)
      {}
      virtual bool update_in( std::string& piece_of_transfer)
      {
        return m_powner_filter->handle_target_data(piece_of_transfer);
      }
      virtual void stop(std::string& OUT collect_remains)
      {

      }
      i_target_handler* m_powner_filter;
    };
  }
}