/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**********/
// "liveMedia"
// Copyright (c) 1996-2003 Live Networks, Inc.  All rights reserved.
// A 'ServerMediaSubsession' object that creates new, unicast, "RTPSink"s
// on demand, from a file.
// C++ header

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#define _FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _SERVER_MEDIA_SESSION_HH
#include "ServerMediaSession.hh"
#endif
#ifndef _RTP_SINK_HH
#include "RTPSink.hh"
#endif

class FileServerMediaSubsession: public ServerMediaSubsession {
protected: // we're a virtual base class
  FileServerMediaSubsession(UsageEnvironment& env, char const* fileName);
  virtual ~FileServerMediaSubsession();

private: // redefined virtual functions
  virtual char const* sdpLines();
  virtual void getStreamParameters(struct sockaddr_in clientAddress,
                                   Port const& clientRTPPort,
                                   Port const& clientRTCPPort,
                                   GroupEId& groupEId,
                                   Boolean& isMulticast,
                                   void*& streamToken);
  virtual void startStream(void* streamToken);
  virtual void pauseStream(void* streamToken);
  virtual void stopStream(void* streamToken);

protected: // new virtual functions
  virtual char const* getAuxSDPLine(RTPSink* rtpSink,
				    FramedSource* inputSource);

protected: // new virtual functions, defined by subclasses
  virtual FramedSource* createNewStreamSource(unsigned& estBitrate) = 0;
      // "estBitrate" is the stream's estimated bitrate, in kbps
  virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
				    unsigned char rtpPayloadTypeIfDynamic,
				    FramedSource* inputSource) = 0;

private:
  void setSDPLinesFromRTPSink(RTPSink* rtpSink, FramedSource* inputSource);
      // used to implement "sdpLines()"

protected:
  char const* fFileName;
  char* fSDPLines;
  char fCNAME[100]; // for RTCP
};

#endif
