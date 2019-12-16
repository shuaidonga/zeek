#include "WeirdState.h"
#include "Net.h"

bool PermitWeird(WeirdStateMap& wsm, std::string_view name, uint64_t threshold,
                 uint64_t rate, double duration)
    {
    auto& state = wsm[string(name)];
	++state.count;

	if ( state.count <= threshold )
		return true;

	if ( state.count == threshold + 1)
		state.sampling_start_time = network_time;
	else
		{
		if ( network_time > state.sampling_start_time + duration )
			{
			state.sampling_start_time = 0;
			state.count = 1;
			return true;
			}
		}

	auto num_above_threshold = state.count - threshold;
	if ( rate )
		return num_above_threshold % rate == 0;
	else
		return false;
    }
