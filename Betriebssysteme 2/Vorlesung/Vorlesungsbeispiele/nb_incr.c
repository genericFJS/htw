void nb_incr (int *var, int offset)
{
  int r1, r2, res;
 label:
  r1 = *var;
  r2 = r1 + offset;
  if ( (res = compare_and_swap(var, r1, r2)) == FALSE) {
    goto label;
  }
}
