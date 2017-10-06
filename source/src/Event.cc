/// \file GenericEvent.cc
/*
 *
 * GenericEvent.cc source template automatically generated by a class generator
 * Creation date : lun. mars 7 2016
 *
 * This file is part of DQM4HEP libraries.
 *
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */

// -- dqm4hep headers
#include <dqm4hep/Event.h>
#include <dqm4hep/StreamingHelper.h>

namespace dqm4hep {

  namespace core {

    Event::Event() :
        m_type(UNKNOWN_EVENT),
        m_source("unknwon"),
        m_timeStamp(),
        m_eventSize(0),
        m_eventNumber(0),
        m_runNumber(0)
    {
    }

    //-------------------------------------------------------------------------------------------------

    Event::~Event()
    {
    }

    //-------------------------------------------------------------------------------------------------

    void Event::clear()
    {
      m_type = UNKNOWN_EVENT;
      m_source = "unknwon";
      m_timeStamp = TimePoint();
      m_eventSize = 0;
      m_eventNumber = 0;
      m_runNumber = 0;
    }

    //-------------------------------------------------------------------------------------------------

    xdrstream::Status Event::writeBase(xdrstream::IODevice *pDevice) const
    {
      uint8_t type(static_cast<uint8_t>(m_type));
      int64_t timeStamp = std::chrono::system_clock::to_time_t(m_timeStamp);

      XDR_STREAM(pDevice->write(&type));
      XDR_STREAM(pDevice->write(&m_source));
      XDR_STREAM(pDevice->write(&timeStamp));
      XDR_STREAM(pDevice->write(&m_eventSize));
      XDR_STREAM(pDevice->write(&m_eventNumber));
      XDR_STREAM(pDevice->write(&m_runNumber));

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    xdrstream::Status Event::readBase(xdrstream::IODevice *pDevice)
    {
      uint8_t type(0);
      int64_t timeStamp(0);

      XDR_STREAM(pDevice->read(&type));
      XDR_STREAM(pDevice->read(&m_source));
      XDR_STREAM(pDevice->read(&timeStamp));
      XDR_STREAM(pDevice->read(&m_eventSize));
      XDR_STREAM(pDevice->read(&m_eventNumber));
      XDR_STREAM(pDevice->read(&m_runNumber));

      this->setType(static_cast<EventType>(type));
      this->setTimeStamp(std::chrono::system_clock::from_time_t(timeStamp));

      return xdrstream::XDR_SUCCESS;
    }

  }

}
