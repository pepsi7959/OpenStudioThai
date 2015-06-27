/**********************************************************************
*  Copyright (c) 2008-2015, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef BEC_FORWARDTRANSLATOR_HPP
#define BEC_FORWARDTRANSLATOR_HPP

#include "BECAPI.hpp"

#include "../utilities/core/Path.hpp"
#include "../utilities/core/Optional.hpp"
#include "../utilities/core/Logger.hpp"
#include "../utilities/core/StringStreamLogSink.hpp"

#include "../model/ModelObject.hpp"

#include <map>

class QDomDocument;
class QDomElement;
class QDomNodeList;

namespace openstudio {

  class ProgressBar;
  class Transformation;

namespace model {
  class Model;
  class ModelObject;
  class Material;
  class ConstructionBase;
  class Facility;
  class Building;
  class BuildingStory;
  class ThermalZone;
  class Space;
  class Surface;
  class SubSurface;
}

namespace bec {

  class BEC_API ForwardTranslator {
  public:
    
    ForwardTranslator();

    virtual ~ForwardTranslator();

    bool modelTobec(const openstudio::model::Model& model, const openstudio::path& path, ProgressBar* progressBar = nullptr);

      /** Get warning messages generated by the last translation. */
    std::vector<LogMessage> warnings() const;

    /** Get error messages generated by the last translation. */
    std::vector<LogMessage> errors() const;

  private:

    QString escapeName(const std::string& name);

    // listed in translation order
    boost::optional<QDomDocument> translateModel(const openstudio::model::Model& model);
    boost::optional<QDomElement> translateFacility(const openstudio::model::Facility& facility, QDomDocument& doc);
    boost::optional<QDomElement> translateBuilding(const openstudio::model::Building& building, QDomDocument& doc);
    boost::optional<QDomElement> translateSpace(const openstudio::model::Space& space, QDomDocument& doc);
    boost::optional<QDomElement> translateSurface(const openstudio::model::Surface& surface, QDomDocument& doc);
    boost::optional<QDomElement> translateSubSurface(const openstudio::model::SubSurface& subSurface, const openstudio::Transformation& transformation, QDomDocument& doc);
    boost::optional<QDomElement> translateThermalZone(const openstudio::model::ThermalZone& thermalZone, QDomDocument& doc);
    boost::optional<QDomElement> translateMaterial(const openstudio::model::Material& material, QDomDocument& doc);
    boost::optional<QDomElement> translateConstructionBase(const openstudio::model::ConstructionBase& constructionBase, QDomDocument& doc);
	boost::optional<QDomElement> translateMyModel(const openstudio::model::Model& model, QDomDocument& doc);

	/* Custom translate */
	boost::optional<QDomElement> translateMySpace(const openstudio::model::Building& space, QDomDocument& doc);
	boost::optional<QDomElement> translateMyElectronicEquipment(const openstudio::model::Space& space, QDomDocument& doc);
	boost::optional<QDomElement> translateMyLights(const openstudio::model::Space& space, QDomDocument& doc);
	boost::optional<QDomElement> translateMyOtherEquipment(const openstudio::model::Space& space, QDomDocument& doc);
	boost::optional<QDomElement> translateMyPeople(const openstudio::model::Space& space, QDomDocument& doc);
	boost::optional<QDomElement> translateMyGasEquipment(const openstudio::model::Space& space, QDomDocument& doc);
	boost::optional<QDomElement> translateMyWaterUse(const openstudio::model::Space space, QDomDocument& doc);
	boost::optional<QDomElement> translateMyLuminaire(const openstudio::model::Space& space, QDomDocument& doc);
	boost::optional<QDomElement> translateMyConstruction(const openstudio::model::Space& space, QDomDocument& doc);


    std::map<openstudio::Handle, QDomElement> m_translatedObjects;

    StringStreamLogSink m_logSink;

    ProgressBar* m_progressBar;

    REGISTER_LOGGER("openstudio.bec.ForwardTranslator");
  };

} // bec
} // openstudio

#endif // BEC_FORWARDTRANSLATOR_HPP
