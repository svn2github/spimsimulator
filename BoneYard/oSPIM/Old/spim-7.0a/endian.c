int
main ()
{
  int x = 0x12345678;

  /* Return 1 for little-endian, 0 for big-endian. */
  return (*(char *)&x == 0x78);
}
