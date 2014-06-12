#include "ruby.h"

VALUE FastHamming = Qnil;

int distance(VALUE _1, VALUE _2);

VALUE create_hamming_pair(VALUE p1, VALUE p2, VALUE dist);

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
  
  ID sym_phash = rb_intern("phash");
  
  for (i = 0; i < new_len; i++) {
    for (j = i+1; j < all_len; j++) {
      i_val = new_arr[i];
      j_val = all_arr[j];
      dist = distance(i_val, j_val);
      if (dist < threshold_as_int) {
        rb_ary_push(list, create_hamming_pair(INT2NUM(i), INT2NUM(j), INT2NUM(dist)));
      }
    }
  }
  return list;
}

VALUE create_hamming_pair(VALUE p1, VALUE p2, VALUE dist) {
  VALUE _1 = rb_str_new2("_1");
  VALUE _2 = rb_str_new2("_2");
  VALUE dist_key = rb_str_new2("dist");
  VALUE hash = rb_hash_new();
  
  rb_hash_aset(hash, _1, p1);
  rb_hash_aset(hash, _2, p2);
  rb_hash_aset(hash, dist_key, dist);
  
  return hash;
}

int distance(VALUE _1, VALUE _2) {
  uint64_t _1_ll;
  uint64_t _2_ll;
  uint64_t differences;
  
  if (_1 == Qnil) {
    return 100;
  } else if (_2 == Qnil) {
    return 100;
  }
  
  _1_ll = NUM2ULL(_1);
  _2_ll = NUM2ULL(_2);
  differences = _1_ll ^ _2_ll; 
 
  return __builtin_popcountll(differences);
}