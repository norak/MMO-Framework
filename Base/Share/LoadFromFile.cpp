/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
������� ������ ��������� 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#include "LoadFromFile.h"

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>

using namespace std;

TLoadFromFile::TLoadFromFile(char* path)
{
 	ReOpen(path);
}
//---------------------------------------------------------------
TLoadFromFile::~TLoadFromFile()
{

}
//---------------------------------------------------------------
bool TLoadFromFile::ReOpen(char* path, bool /*append*/)
{
  Close();

	if(path!=NULL)
    sPath = path;

	if(sPath.size()==0) 
    return false;

	pFile = fopen(sPath.data(), "rb");
	if(pFile!=NULL) return true;

	return false;
}
//---------------------------------------------------------------
unsigned int TLoadFromFile::Size()
{
#ifdef WIN32
	int fd = _fileno(pFile);

  if(fd<0) return 0;

  struct _stat buffer;
  int resstat = _fstat( fd,&buffer);
  if(resstat!=0) return 0;

  return buffer.st_size;
#else
  int fd = fileno(pFile);

  if(fd<0) return 0;

  struct stat buffer;
  int resstat = fstat( fd,&buffer);
  if(resstat!=0) return 0;

  return buffer.st_size;
#endif
}
//---------------------------------------------------------------
int TLoadFromFile::ReadSmall(TContainer& c)
{
  c.SetDataByCount(NULL, Size());
  return Read( c.GetPtr(), c.GetSize(), 0);
}
//---------------------------------------------------------------
unsigned int TLoadFromFile::Read(void* buffer, unsigned int size, unsigned int offset)
{
  int res = _fseeki64( pFile, __int64(offset), SEEK_SET);

  //int res = fseek(pFile, offset, SEEK_SET);
  if(res!=0) return 0;

  if(Size()<offset) return 0;
  unsigned int max_read = Size() - offset;

  fread(buffer, size, 1, pFile);
  return min(max_read, size);
}
//---------------------------------------------------------------
