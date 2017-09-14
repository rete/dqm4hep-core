/// \file QualityTest.cc
/*
 *
 * QualityTest.cc source template automatically generated by a class generator
 * Creation date : ven. f�vr. 20 2015
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
 * @author Remi Ete, DESY
 */

// -- dqm4hep headers
#include "dqm4hep/QualityTest.h"
#include "dqm4hep/Logging.h"
#include "dqm4hep/MonitorElement.h"

namespace dqm4hep {

  namespace core {

    QualityTestReport::QualityTestReport() :
      m_name(""),
      m_type(""),
      m_monitorElementName(""),
      m_monitorElementType(""),
      m_message(""),
      m_quality(0.f),
      m_isSuccessful(true),
      m_extraInfos(Json::objectValue)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    QualityTestReport::QualityTestReport(const QualityTestReport &qreport)
    {
      *this = qreport;
    }

    //-------------------------------------------------------------------------------------------------

    QualityTestReport &QualityTestReport::operator=(const QualityTestReport &qreport)
    {
      m_name = qreport.m_name;
      m_type = qreport.m_type;
      m_monitorElementName = qreport.m_monitorElementName;
      m_monitorElementType = qreport.m_monitorElementType;
      m_message = qreport.m_message;
      m_quality = qreport.m_quality;
      m_isSuccessful = qreport.m_isSuccessful;
      m_extraInfos = qreport.m_extraInfos;

      return *this;
    }

    //-------------------------------------------------------------------------------------------------

    void QualityTestReport::toJson(Json::Value &value) const
    {
      value["type"] = m_type;
      value["name"] = m_name;
      value["monitorElementName"] = m_monitorElementName;
      value["monitorElementType"] = m_monitorElementType;
      value["message"] = m_message;
      value["quality"] = static_cast<int>(m_quality);
      value["successful"] = m_isSuccessful;
      value["extra"] = m_extraInfos;
    }

    //-------------------------------------------------------------------------------------------------

    void QualityTestReport::fromJson(const Json::Value &value)
    {
      m_type = value.get("type", m_type).asString();
      m_name = value.get("name", m_name).asString();
      m_monitorElementType = value.get("monitorElementType", m_monitorElementType).asString();
      m_monitorElementName = value.get("monitorElementName", m_monitorElementName).asString();
      m_message = value.get("message", m_message).asString();
      m_quality = value.get("quality", m_quality).asFloat();
      m_isSuccessful = value.get("successful", m_isSuccessful).asBool();
      m_extraInfos = value.get("extra", m_extraInfos);
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    QualityTest::QualityTest(const std::string &type, const std::string &name) :
      m_type(type),
	    m_name(name)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    QualityTest::~QualityTest()
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    const std::string &QualityTest::type() const
    {
      return m_type;
    }

    //-------------------------------------------------------------------------------------------------

    const std::string &QualityTest::name() const
    {
      return m_name;
    }

    //-------------------------------------------------------------------------------------------------

    void QualityTest::run(MonitorElement *pMonitorElement, QualityTestReport &report)
    {
      this->fillBasicInfo(pMonitorElement, report);

      if(!this->canRun(pMonitorElement))
      {
        report.m_message = "Couldn't run quality test: canRun() failed";
        report.m_quality = 0.f;
        report.m_isSuccessful = false;
        return;
      }

      try
      {
        THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->userRun(pMonitorElement, report));
      }
      catch(StatusCodeException &exception)
      {
        const std::string message("Caught StatusCodeException while run QTest: " + exception.toString());

        if(!report.m_message.empty())
          report.m_message + " " + message;
        else
          report.m_message = message;

        report.m_quality = 0.f;
        report.m_isSuccessful = false;
      }
      catch(...)
      {
        const std::string message("Caught unknown exception while run QTest");

        if(!report.m_message.empty())
          report.m_message + " " + message;
        else
          report.m_message = message;

        report.m_quality = 0.f;
        report.m_isSuccessful = false;
      }
    }

    //-------------------------------------------------------------------------------------------------

    void QualityTest::fillBasicInfo(MonitorElement *pMonitorElement, QualityTestReport &report) const
    {
      report.m_name = this->name();
      report.m_type = this->type();
      report.m_monitorElementType = pMonitorElement->type();
      report.m_monitorElementName = pMonitorElement->name();
      report.m_quality = 0.f;
      report.m_message = "";
      report.m_isSuccessful = false;
      report.m_extraInfos.clear();
    }

  }

}
