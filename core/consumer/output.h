/*
* Copyright (c) 2011 Sveriges Television AB <info@casparcg.com>
*
* This file is part of CasparCG (www.casparcg.com).
*
* CasparCG is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* CasparCG is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with CasparCG. If not, see <http://www.gnu.org/licenses/>.
*
* Author: Robert Nagy, ronag89@gmail.com
*/

#pragma once

#include <common/forward.h>
#include <common/memory/safe_ptr.h>
#include <common/reactive.h>

#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree_fwd.hpp>

FORWARD1(boost, template<typename> class unique_future)
FORWARD2(caspar, diagnostics, class graph);

namespace caspar { namespace core {
	
class output sealed : boost::noncopyable
{
public:
	explicit output(const struct video_format_desc& format_desc, int channel_index);
	
	// output

	void operator()(safe_ptr<const struct frame> frame, const struct video_format_desc& format_desc);
	
	void add(const safe_ptr<struct frame_consumer>& consumer);
	void add(int index, const safe_ptr<struct frame_consumer>& consumer);
	void remove(const safe_ptr<struct frame_consumer>& consumer);
	void remove(int index);
	
	boost::unique_future<boost::property_tree::wptree> info() const;

private:
	struct impl;
	safe_ptr<impl> impl_;
};

}}