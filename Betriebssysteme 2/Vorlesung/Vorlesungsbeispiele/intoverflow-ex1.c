int copybuffer (char *buffer, int len)
{
  char mybuffer[800];
  if (len > sizeof(mybuffer)) {
    return -1;
  }
  return memcpy(mybuffer, buffer, len);
}
