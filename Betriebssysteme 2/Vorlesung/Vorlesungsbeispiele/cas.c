int compare_and_swap(T *location, T oldValue, T newValue)
{
  <begin atomic>
  if (*location == oldValue) {
    *location = newValue;
    return TRUE;
  }
  else {
    return FALSE;	  
  }
  <end atomic>
}
