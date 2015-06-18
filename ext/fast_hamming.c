#include "ruby.h"

// Don't allow the number of pairs collected to exceed MAX_PAIRS.
const int MAX_PAIRS = 1250000;

VALUE FastHamming = Qnil;

int distance(VALUE _1, VALUE _2);

VALUE create_hamming_pair(VALUE p1, VALUE p2);

void Init_fast_hamming();

VALUE method_all_hamming_pairs(VALUE self, VALUE new_media, VALUE all_media, VALUE threshold);

void Init_fast_hamming() {
  FastHamming = rb_define_module("FastHamming");
  rb_define_module_function(FastHamming, "all_hamming_pairs", method_all_hamming_pairs, 3);
}

VALUE method_all_hamming_pairs(VALUE self, VALUE new_media, VALUE all_media, VALUE threshold) {
  int i, j, k;
  VALUE i_val, j_val;
  int dist;

  int threshold_as_int = NUM2INT(threshold);
  int new_len = RARRAY_LEN(new_media);
  int all_len = RARRAY_LEN(all_media);
  VALUE *new_arr = RARRAY_PTR(new_media);
  VALUE *all_arr = RARRAY_PTR(all_media);
  VALUE list = rb_ary_new();

  int pair_count = 0;
  for (i = 0; i < new_len; i++) {
    for (j = i+1; j < all_len; j++) {
      i_val = new_arr[i];
      j_val = all_arr[j];
      dist = distance(i_val, j_val);
      if (dist < threshold_as_int) {
        rb_ary_push(list, create_hamming_pair(INT2NUM(i), INT2NUM(j)));

        pair_count++;
        if (pair_count >= MAX_PAIRS) {
          return list;
        }
      }
    }
  }
  return list;
}

VALUE create_hamming_pair(VALUE p1, VALUE p2) {
  return rb_ary_new3(2, p1, p2);
}

int distance(VALUE _1, VALUE _2) {
  uint64_t _1_ll;
  uint64_t _2_ll;
  uint64_t differences;
  const int max_dist = 64;

  if (_1 == Qnil) {
    return max_dist;
  } else if (_2 == Qnil) {
    return max_dist;
  }

  _1_ll = NUM2ULL(_1);
  _2_ll = NUM2ULL(_2);
  differences = _1_ll ^ _2_ll;

  return __builtin_popcountll(differences);
}