/***************************************************************************************
 * Original Author:		Gabriele Giuseppini
 * Created:				2018-01-21
 * Copyright:			Gabriele Giuseppini  (https://github.com/GabrieleGiuseppini)
 ***************************************************************************************/
#include "Material.h"

#include "Utils.h"

std::unique_ptr<Material> Material::Create(picojson::object const & materialJson)
{
	std::string name = Utils::GetOptionalJsonMember<std::string>(materialJson, "name", "Unspecified");

    picojson::object massJson = Utils::GetMandatoryJsonObject(materialJson, "mass");
    float mass = static_cast<float>(Utils::GetMandatoryJsonMember<double>(massJson, "nominal_mass"))
               * static_cast<float>(Utils::GetMandatoryJsonMember<double>(massJson, "density"));

    float strength = static_cast<float>(Utils::GetOptionalJsonMember<double>(materialJson, "strength", 1.0));
    float stiffness = static_cast<float>(Utils::GetOptionalJsonMember<double>(materialJson, "stiffness", 1.0));
	
    std::array<uint8_t, 3u> structuralColourRgb = Utils::Hex2RgbColour(Utils::GetMandatoryJsonMember<std::string>(materialJson, "structural_colour"));
    std::array<uint8_t, 3u> renderColourRgb = Utils::Hex2RgbColour(Utils::GetMandatoryJsonMember<std::string>(materialJson, "render_colour"));
	bool isHull = Utils::GetMandatoryJsonMember<bool>(materialJson, "is_hull");
    bool isRope = Utils::GetOptionalJsonMember<bool>(materialJson, "is_rope", false);

	std::optional<ElectricalProperties> electricalProperties;
	std::optional<picojson::object> electricalPropertiesJson = Utils::GetOptionalJsonObject(materialJson, "electrical_properties");
	if (!!electricalPropertiesJson)
	{
		std::string elementTypeStr = Utils::GetMandatoryJsonMember<std::string>(*electricalPropertiesJson, "element_type");
        ElectricalProperties::ElectricalElementType elementType = ElectricalProperties::StrToElectricalElementType(elementTypeStr);

        bool isSelfPowered = Utils::GetMandatoryJsonMember<bool>(*electricalPropertiesJson, "is_self_powered");

		electricalProperties.emplace(
			elementType,
            isSelfPowered);
	}

    std::optional<SoundProperties> soundProperties;
    std::optional<picojson::object> soundPropertiesJson = Utils::GetOptionalJsonObject(materialJson, "sound_properties");
    if (!!soundPropertiesJson)
    {        
        std::string elementTypeStr = Utils::GetMandatoryJsonMember<std::string>(*soundPropertiesJson, "element_type");
        SoundProperties::SoundElementType elementType = SoundProperties::StrToSoundElementType(elementTypeStr);

        soundProperties.emplace(
            elementType);
    }

	return std::unique_ptr<Material>(
		new Material(
			name,
			strength,
			mass,
            stiffness,
            structuralColourRgb,
            renderColourRgb,
			isHull,
            isRope,
			electricalProperties,
            soundProperties));
}
