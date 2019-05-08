
int
validChoice (char *a, int begin, int end)
{
  int len = strlen (a);
  if (!(a[0] >= begin && a[0] <= end) || len != 1)
    {
      printf ("!!ERROR: Please Enter NUMBER in Range\n");
      return 0;
    }
  return 1;
}

int
validString (char *a)
{
  int i, flag = 0;
  for (i = 0; i < strlen (a); i++)
    {
      if (!isalpha (a[i]))
	{
	  flag = 1;
	}
    }

  if (flag == 1)
    {
      printf ("!!ERROR: Please enter a valid Name\n");
      return 0;
    }
  else
    return 1;
}

int
validNumber (char *num)
{
  int i, flag = 0;
  for (i = 0; i < strlen (num); i++)
    {
      if (!isdigit (num[i]))
	flag = 1;
    }
  if (flag == 1)
    {
      printf ("!!ERROR: Please enter phone Number \n");
      return 0;
    }
  else
    return 1;
}

int
validDate (int dd, int mm, int yy)
{

  if (yy >= 1700 && yy <= 2018)
    {
      //check month
      if (mm >= 1 && mm <= 12)
	{
	  //check days
	  if ((dd >= 1 && dd <= 31)
	      && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8
		  || mm == 10 || mm == 12))
	    return 1;
	  else if ((dd >= 1 && dd <= 30)
		   && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
	    return 1;
	  else if ((dd >= 1 && dd <= 28) && (mm == 2))
	    return 1;
	  else if (dd == 29 && mm == 2
		   && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
	    return 1;
	  else
	    {
	      printf ("!!ERROR: Please enter a valid day\n");
	      printf ("%d is not a valid day\n", dd);
	      return 0;
	    }
	}
      else
	{
	  printf ("!!ERROR: Please enter a valid month\n");
	  printf ("%d is not a valid month\n", mm);

	  return 0;
	}

    }
  else
    {
      printf ("!!ERROR: Please enter a valid year\n");
      printf ("%d is not a valid year\n", yy);

      return 0;

    }
}

int
validEmail (char *email)
{
  int len = strlen (email);
  int flag = 0, i, j;
  char last[4];
  if ((isalpha (email[0]) || isdigit (email[0])) && email[len - 4] == '.')
    {
      for (i = 1; i < len - 8; i++)
	{
	  if (email[i] == '@')
	    {
	      for (i = len - 3, j = 0; i < len; i++, j++)
		{
		  last[j] = email[i];
		}
	      last[3] = '\0';
	      if (strcmp (last, "net") == 0 || strcmp (last, "com") == 0
		  || strcmp (last, "org") == 0 || strcmp (last, "edu") == 0)
		{
		  flag = 1;
		}
	    }
	}
      if (flag)
	{
	  return 1;
	}
      else
	{
	  printf ("Invalid Email\n");
	  return 0;
	}
    }
  else
    {
      printf ("Invalid Email1\n");
      return 0;
    }
}
