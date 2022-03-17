#include "NFS2/TRK/StructureRefBlock.h"
#include "Common/Utils.h"

using namespace LibOpenNFS::NFS2;

StructureRefBlock::StructureRefBlock(std::istream &trk)
{
    assert(this->SerializeIn(trk) && "Failed to serialize StructureRefBlock from file stream");
}

bool StructureRefBlock::SerializeIn(std::istream &ifstream)
{
    std::streamoff padCheck = ifstream.tellg();

    Utils::SafeRead(ifstream, recSize);
    Utils::SafeRead(ifstream, recType);
    Utils::SafeRead(ifstream, structureRef);

    if (recType == 1)
    {
        // Fixed type
        Utils::SafeRead(ifstream, refCoordinates);
    }
    else if (recType == 3)
    {
        // Animated type
        Utils::SafeRead(ifstream, animLength);
        Utils::SafeRead(ifstream, unknown);
        animationData.resize(animLength);
        Utils::SafeRead(ifstream, animationData.begin(), animationData.end());
    }
    else if (recType == 4)
    {
        // 4 Component PSX Vert data? TODO: Restructure to allow the 4th component to be read
        Utils::SafeRead(ifstream, refCoordinates);
    }
    else
    {
        //LOG(DEBUG) << "Unknown Structure Reference type: " << (int) recType << " Size: " << (int) recSize << " StructRef: " << (int) structureRef;
        return true;
    }

    ifstream.seekg(recSize - (ifstream.tellg() - padCheck), std::ios_base::cur); // Eat possible padding

    return true;
}

void StructureRefBlock::SerializeOut(std::ostream &ofstream)
{
    assert(false && "StructureRefBlock output serialization is not currently implemented");
}
