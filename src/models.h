typedef struct DataObject
{
    int dataInt;
    char dataText[255];
}DataObject;

void swapDataObject (DataObject * obj1, DataObject * obj2)
{
    DataObject *temp;
    temp = obj1;
    obj1 = obj2;
    obj2 = temp;
    return;
}

DataObject *DO_New_s (char * dataContent)
{
    int i, j;
    char propertyCache[255];
    DataObject *thisData = (DataObject *)malloc(sizeof (DataObject));
    for (i=0, j=0; dataContent[i] != '?'; i++, j++)
        propertyCache[j] = dataContent[i];
    propertyCache[j] = '\0';
    thisData->dataInt = atoi(propertyCache);
    for (++i, j=0; dataContent[i] != '\n' && dataContent[i] != '\0'; i++, j++)
        propertyCache[j] = dataContent[i];
    propertyCache[j] = '\0';
    strcpy(thisData->dataText, propertyCache);
    return thisData;
}

DataObject *DO_New (int dataInt, char * dataText)
{
    DataObject *thisData = (DataObject *)malloc(sizeof (DataObject));
    thisData->dataInt = dataInt;
    strcpy(thisData->dataText, dataText);
    return thisData;
}

char * DO_serialize (DataObject obj) {
    static char res[80];
    sprintf(res, "%d\?%s", obj.dataInt, obj.dataText);
    return res;
}

int DO_print (DataObject obj) {
    printf("%s\n", DO_serialize(obj));
    return 0;
}
