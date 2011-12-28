/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */
#ifndef DISCOVERYCLIENT_H
#define DISCOVERYCLIENT_H

#include <QUdpSocket>

namespace mtdnd {


  class DiscoveryClient : public QUdpSocket
  {
      Q_OBJECT
  public:
    explicit DiscoveryClient(const int discoveryPort);
    void discover();
  private:
    int discoveryPort;
  private slots:
    void process();
  signals:
    void discovered(const QString serverHost, int assetPort, int commandPort);


  };
}

#endif // DISCOVERYCLIENT_H
