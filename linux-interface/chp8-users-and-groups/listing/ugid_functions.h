#ifndef UGID_FUNCTIONS_H_
#define UGID_FUNCTIONS_H

char* userNameFromId(__uid_t uid);
__uid_t userIdFromName(const char *name);
char* groupNameFromId(__gid_t gid);
__gid_t groupIdFromName(const char *name);

#endif