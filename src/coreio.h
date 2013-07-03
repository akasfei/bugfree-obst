DataObject * readData (char * filename)
{
  FILE *thisfile = fopen(filename, "r");
  char fileBuffer[255];
  DataObject * dataList[255], * objArray;
  int i = 0, j;
  do
  {
    fgets(fileBuffer, 255, thisfile);
    dataList[i] = DO_New_s(fileBuffer);
    i++;
  }while ( !feof(thisfile) );
  objArray = (DataObject *)malloc(i * sizeof(DataObject));
  for (j = 0; j < i; j++)
  {
    objArray[j] = *dataList[j];
    free(dataList[j]);
  }
  return objArray;
}
