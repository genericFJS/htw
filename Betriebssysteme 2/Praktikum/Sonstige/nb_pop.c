T pop(void)
{
  T *old_sp, *new_sp, elem;
 retry:
  old_sp = SP;
  new_sp = old_sp + 1;
  elem = *old_sp;
  if ( (CAS(&SP, old_sp, new_sp) == FALSE) ) {
    goto retry;
  }
  return elem;
}
