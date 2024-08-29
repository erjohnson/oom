// Bit board example by Jeroen van Rijn
package bit_board

import "core:fmt"

Bitboard :: distinct [7]bit_set[0 ..< 32;u32]

CELL_COUNT :: 217

bit_to_col_row :: proc(bit: int) -> (col, row: int) {
	assert(0 <= bit && bit < CELL_COUNT)
	col = bit % 32
	row = bit / 32
	return
}

bb_set_bit :: proc(bb: ^Bitboard, bit: int) {
	col, row := bit_to_col_row(bit)
	bb^[row] |= {col}
}

bb_get_bit :: proc(bb: Bitboard, bit: int) -> bool {
	col, row := bit_to_col_row(bit)
	return col in bb[row]
}

Bitboard_Iterator :: struct {
	bb:  Bitboard,
	idx: int,
}

make_bb_iterator :: proc(bb: Bitboard) -> (it: Bitboard_Iterator) {
	it.bb = bb
	return
}

bb_iterator :: proc(it: ^Bitboard_Iterator) -> (col, row: int, ok: bool) {
	// Find index to return
	for idx := it.idx; idx < CELL_COUNT; idx += 1 {
		if bb_get_bit(it.bb, idx) {
			it.idx = idx + 1
			col, row = bit_to_col_row(idx)
			ok = true
			break
		}
	}
	return
}

primes := []int{
      2,   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
     73,  79,  83,  89,  97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211,
}

main :: proc() {
	b: Bitboard
	for p in primes {
		bb_set_bit(&b, p)
	}

	for p in primes {
		assert(bb_get_bit(b, p))
	}

	it := make_bb_iterator(b)
	idx := 0

	fmt.println("Hellope!")
	for x, y in bb_iterator(&it) {
		fmt.printf("%v,", y * 32 + x)
		assert(primes[idx] == y * 32 + x)
		idx += 1
	}
	fmt.println()
	assert(len(primes) == idx)
}
