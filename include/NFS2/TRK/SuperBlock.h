#pragma once

#include <cstdint>
#include <vector>

#include "Common/Enums.h"
#include "Common/ISerializable.h"
#include "NFS2/Common.h"
#include "NFS2/TRK/TrackBlock.h"

namespace LibOpenNFS
{
    namespace NFS2
    {
        template <typename Platform>
        class SuperBlock : public IDeserializable
        {
        public:
            // Raw file data
            uint32_t superBlockSize;
            uint32_t nBlocks;
            uint32_t padding;
            std::vector<TrackBlock<Platform>> trackBlocks;
            std::vector<uint32_t> blockOffsets;

        private:
            void SerializeIn(std::istream &ifstream) override;
        };
    } // namespace NFS2
} // namespace LibOpenNFS
