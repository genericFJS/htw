void push(T elem)
{
  T *old_sp, *new_sp, old_val;
 retry:
  old_sp = SP;
  new_sp = old_sp - 1;
  old_val = *new_sp;
  if ( (CAS2(&SP, new_sp, old_sp, old_val, new_sp, elem) == FALSE) ) {
    goto retry;
  }
}
