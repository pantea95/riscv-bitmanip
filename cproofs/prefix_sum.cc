/*
 *  Copyright (C) 2018  Clifford Wolf <clifford@clifford.at>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include "common.h"

// ---------------------------------------------------------

uint32_t prefix_byte_nibbles_reference(uint32_t src)
{
	uint32_t a = 0;

	uint32_t k = 0x11111111;
	for (int i = 0; i < 8; i++) {
		if ((src >> i) & 1)
			a += k;
		k = k << 4;
	}

	return a;
}

uint32_t prefix_byte_nibbles_impl(uint32_t src)
{
	uint32_t a0, a1;

	a0 = src & 0xff;
	a0 = zip32(a0);
	a0 = zip32(a0);

	a1 = sll32(a0, 4);
	a0 += a1;

	a1 = sll32(a0, 8);
	a0 += a1;

	a1 = sll32(a0, 16);
	a0 += a1;

	return a0;
}

void prefix_byte_nibbles_check(uint32_t src)
{
	uint32_t a = prefix_byte_nibbles_reference(src);
	uint32_t b = prefix_byte_nibbles_impl(src);
	assert(a == b);
}