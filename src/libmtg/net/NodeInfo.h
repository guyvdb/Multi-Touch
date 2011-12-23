#ifndef NODEINFO_H
#define NODEINFO_H

#include <QString>

namespace mtg {

  class NodeInfo
  {
  public:
      NodeInfo(const QString id, const QString host, const int port);
      QString id;
      QString host;
      int port;
  };


}

#endif // NODEINFO_H
