#include "snd_MmlParser.h"
#include "snd_MmlSeqTrack.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			MmlSeqTrack::MmlSeqTrack()
			{
				mMmlParserParam.BOOL_0x1 = true;
				mMmlParserParam.BOOL_0x2 = false;
				mMmlParserParam.mPredicate = true;
				mMmlParserParam.mStackIndex = 0;
			}
			
			UNKWORD MmlSeqTrack::Parse(bool b)
			{
				return mParser->Parse(this, b);
			}
		}
	}
}