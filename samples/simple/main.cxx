/*
 * main.cxx
 *
 * A simple H.323 "net telephone" application.
 *
 * Copyright (c) 2000 Equivalence Pty. Ltd.
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is Portable Windows Library.
 *
 * The Initial Developer of the Original Code is Equivalence Pty. Ltd.
 *
 * Contributor(s): ______________________________________.
 *
 * $Log: main.cxx,v $
 * Revision 1.2002  2001/07/30 07:22:25  robertj
 * Abstracted listener management from H.323 to OpalEndPoint class.
 *
 * Revision 2.0  2001/07/27 15:48:24  robertj
 * Conversion of OpenH323 to Open Phone Abstraction Library (OPAL)
 *
 * Revision 1.12  2001/07/13 08:44:16  robertj
 * Fixed incorrect inclusion of hardware codec capabilities.
 *
 * Revision 1.11  2001/05/17 07:11:29  robertj
 * Added more call end types for common transport failure modes.
 *
 * Revision 1.10  2001/05/14 05:56:26  robertj
 * Added H323 capability registration system so can add capabilities by
 *   string name instead of having to instantiate explicit classes.
 *
 * Revision 1.9  2001/03/21 04:52:40  robertj
 * Added H.235 security to gatekeepers, thanks F�rbass Franz!
 *
 * Revision 1.8  2001/03/20 23:42:55  robertj
 * Used the new PTrace::Initialise function for starting trace code.
 *
 * Revision 1.7  2000/10/16 08:49:31  robertj
 * Added single function to add all UserInput capability types.
 *
 * Revision 1.6  2000/07/31 14:08:09  robertj
 * Added fast start and H.245 tunneling flags to the H323Connection constructor so can
 *    disabled these features in easier manner to overriding virtuals.
 *
 * Revision 1.5  2000/06/20 02:38:27  robertj
 * Changed H323TransportAddress to default to IP.
 *
 * Revision 1.4  2000/06/07 05:47:55  robertj
 * Added call forwarding.
 *
 * Revision 1.3  2000/05/23 11:32:27  robertj
 * Rewrite of capability table to combine 2 structures into one and move functionality into that class
 *    allowing some normalisation of usage across several applications.
 * Changed H323Connection so gets a copy of capabilities instead of using endponts, allows adjustments
 *    to be done depending on the remote client application.
 *
 * Revision 1.2  2000/05/11 10:00:02  robertj
 * Fixed setting and resetting of current call token variable.
 *
 * Revision 1.1  2000/05/11 04:05:57  robertj
 * Simple sample program.
 *
 */

#include <ptlib.h>

#include <lids/lidep.h>
#include <h323/h323ep.h>
#include <h323/gkclient.h>

#include "main.h"
#include "version.h"


#ifdef OPAL_STATIC_LINK
#include <codec/gsmcodec.h>
const OpalMediaFormat * OPAL_GSM_Force_Inclusion = &OpalMediaFormat_GSM;
#endif


#define new PNEW


PCREATE_PROCESS(SimpleOpalProcess);


///////////////////////////////////////////////////////////////

SimpleOpalProcess::SimpleOpalProcess()
  : PProcess("Open Phone Abstraction Library", "SimpleOpal",
             MAJOR_VERSION, MINOR_VERSION, BUILD_TYPE, BUILD_NUMBER)
{
}


void SimpleOpalProcess::Main()
{
  cout << GetName()
       << " Version " << GetVersion(TRUE)
       << " by " << GetManufacturer()
       << " on " << GetOSClass() << ' ' << GetOSName()
       << " (" << GetOSVersion() << '-' << GetOSHardware() << ")\n\n";

  // Get and parse all of the command line arguments.
  PArgList & args = GetArguments();
  args.Parse(
             "a-auto-answer."
             "b-bandwidth:"
             "B-forward-busy:"
             "D-disable:"
             "e-silence."
             "f-fast-disable."
             "g-gatekeeper:"
             "h-help."
             "i-interface:"
             "j-jitter:"
             "l-listen."
             "n-no-gatekeeper."
#if PTRACING
             "o-output:"
#endif
             "P-prefer:"
#ifdef P_SSL
             "p-password:"
#endif
             "q-quicknet:"
             "r-require-gatekeeper."
             "s-sound:"
             "-sound-in:"
             "-sound-out:"
             "T-h245tunneldisable."
#if PTRACING
             "t-trace."
#endif
             "u-user:"
          , FALSE);


  if (args.HasOption('h') || (!args.HasOption('l') && args.GetCount() == 0)) {
    cout << "Usage : " << GetName() << " [options] -l\n"
            "      : " << GetName() << " [options] [alias@]hostname   (no gatekeeper)\n"
            "      : " << GetName() << " [options] alias[@hostname]   (with gatekeeper)\n"
            "Options:\n"
            "  -l --listen             : Listen for incoming calls.\n"
            "  -g --gatekeeper host    : Specify gatekeeper host.\n"
            "  -n --no-gatekeeper      : Disable gatekeeper discovery.\n"
            "  -r --require-gatekeeper : Exit if gatekeeper discovery fails.\n"
            "  -a --auto-answer        : Automatically answer incoming calls.\n"
            "  -u --user name          : Set local alias name(s) (defaults to login name).\n"
            "  -b --bandwidth bps      : Limit bandwidth usage to bps bits/second.\n"
            "  -j --jitter delay       : Set jitter buffer to delay milliseconds.\n"
            "  -D --disable codec      : Disable the specified codec (may be used multiple times)\n"
            "  -P --prefer codec       : Prefer the specified codec (may be used multiple times)\n"
            "  -i --interface ipnum    : Select interface to bind to.\n"
            "  -B --forward-busy party : Forward to remote party if busy.\n"
            "  -e --silence            : Disable transmitter silence detection.\n"
            "  -f --fast-disable       : Disable fast start.\n"
            "  -T --h245tunneldisable  : Disable H245 tunnelling.\n"
            "  -q --quicknet device    : Select Quicknet xJACK device.\n"
            "  -s --sound device       : Select sound input/output device.\n"
            "     --sound-in device    : Select sound input device.\n"
            "     --sound-out device   : Select sound output device.\n"
#if PTRACING
            "  -t --trace              : Enable trace, use multiple times for more detail.\n"
            "  -o --output             : File for trace output, default is stderr.\n"
#endif
            "  -h --help               : This help message.\n"
            << endl;
    return;
  }

#if PTRACING
  PTrace::Initialise(args.GetOptionCount('t'),
                     args.HasOption('o') ? (const char *)args.GetOptionString('o') : NULL);
#endif

  // Create the Opal Manager and initialise it
  opal = new MyManager;

  if (opal->Initialise(args))
    opal->Main(args);

  delete opal;

  cout << "Exiting " << GetName() << endl;
}


///////////////////////////////////////////////////////////////

MyManager::MyManager()
{
  potsEP = NULL;
  pcssEP = NULL;
}


MyManager::~MyManager()
{
  if (potsEP != NULL)
    potsEP->RemoveLinesFromDevice(xJack);
}


BOOL MyManager::Initialise(PArgList & args)
{
  // Set the various options
  autoAnswer           = args.HasOption('a');
  silenceOn            = !args.HasOption('e');
  busyForwardParty     = args.GetOptionString('B');

  if (args.HasOption('j')) {
    unsigned jitter = args.GetOptionString('j').AsUnsigned();
    if (jitter >= 20 && jitter <= 10000)
      SetMaxAudioDelayJitter(jitter);
    else {
      cerr << "Jitter should be between 20 milliseconds and 10 seconds." << endl;
      return FALSE;
    }
  }

  cout << "Auto answer is " << (autoAnswer ? "on" : "off") << "\n"
          "Silence supression is " << silenceOn << "\n"
          "Jitter buffer: "  << GetMaxAudioDelayJitter() << " ms" << endl;


  ///////////////////////////////////////
  // Open the LID if parameter provided, create LID based endpoint

  PString device = args.GetOptionString('q');
  if (device.IsEmpty() || device == "*") {
    PStringArray devices = OpalIxJDevice::GetDeviceNames();
    if (devices.GetSize() > 0)
      device = devices[0];
    else
      device = PString();
  }
  if (!device) {
    if (xJack.Open(device)) {
      // Create LID protocol handler, automatically adds to manager
      potsEP = new OpalPOTSEndPoint(*this);
      if (potsEP->AddLinesFromDevice(xJack))
        cout << "Quicknet device is " << device << endl;
      else {
        RemoveEndPoint(potsEP);
        potsEP = NULL;
      }
    }
    else
      cerr << "Could not open device \"" << device << '"' << endl;
  }


  ///////////////////////////////////////
  // Create PC Sound System handler

  pcssEP = new MyPCSSEndPoint(*this);

  if (!pcssEP->SetSoundDevice(args, "sound", PSoundChannel::Recorder))
    return FALSE;
  if (!pcssEP->SetSoundDevice(args, "sound", PSoundChannel::Player))
    return FALSE;
  if (!pcssEP->SetSoundDevice(args, "sound-in", PSoundChannel::Recorder))
    return FALSE;
  if (!pcssEP->SetSoundDevice(args, "sound-out", PSoundChannel::Player))
    return FALSE;

  cout << "Sound output device: \"" << pcssEP->GetSoundChannelPlayDevice() << "\"\n"
          "Sound  input device: \"" << pcssEP->GetSoundChannelRecordDevice() << '"' << endl;


  ///////////////////////////////////////
  // Create H.323 protocol handler

  H323EndPoint * h323 = new H323EndPoint(*this);

  noFastStart      = args.HasOption('f');
  noH245Tunnelling = args.HasOption('h');

  // Get local username, multiple uses of -u indicates additional aliases
  if (args.HasOption('u')) {
    PStringArray aliases = args.GetOptionString('u').Lines();
    h323->SetLocalUserName(aliases[0]);
    for (PINDEX i = 1; i < aliases.GetSize(); i++)
      h323->AddAliasName(aliases[i]);
  }

  if (args.HasOption('b')) {
    unsigned initialBandwidth = args.GetOptionString('b').AsUnsigned()*100;
    if (initialBandwidth == 0) {
      cerr << "Illegal bandwidth specified." << endl;
      return FALSE;
    }
    h323->SetInitialBandwidth(initialBandwidth);
  }

  // Set the default codecs available on sound cards.
  h323->AddAllCapabilities(0, 0, "GSM*{sw}");
  h323->AddAllCapabilities(0, 0, "G.711*{sw}");
  h323->AddAllCapabilities(0, 0, "LPC*{sw}");
  h323->AddAllUserInputCapabilities(0, 1);

  h323->RemoveCapabilities(args.GetOptionString('D').Lines());
  h323->ReorderCapabilities(args.GetOptionString('P').Lines());

  cout << "Local username: " << h323->GetLocalUserName() << "\n"
       << "FastConnect is " << !noFastStart << "\n"
       << "H245Tunnelling is " << noH245Tunnelling << "\n"
       <<  "Codecs (in preference order):\n" << setprecision(2) << h323->GetCapabilities() << endl;


  // Start the listener thread for incoming calls.
  if (args.HasOption('i')) {
    PStringArray listeners = args.GetOptionString('i').Lines();
    if (!h323->StartListeners(listeners)) {
      cerr <<  "Could not open any H.323 listener from "
           << setfill(',') << listeners << endl;
      return FALSE;
    }
  }
  else {
    if (!h323->StartListener(NULL)) {
      cerr <<  "Could not open H.323 listener on TCP port "
           << h323->GetDefaultSignalPort() << endl;
      return FALSE;
    }
  }


  // Establish link with gatekeeper if required.
  if (args.HasOption('g')) {
    PString gkName = args.GetOptionString('g');
    OpalTransportUDP * rasChannel;
    if (args.GetOptionString('i').IsEmpty())
      rasChannel  = new OpalTransportUDP(*h323);
    else {
      PIPSocket::Address interfaceAddress(args.GetOptionString('i'));
      rasChannel  = new OpalTransportUDP(*h323, interfaceAddress);
    }
    if (h323->SetGatekeeper(gkName, rasChannel))
      cout << "Gatekeeper set: " << *h323->GetGatekeeper() << endl;
    else {
      cerr << "Error registering with gatekeeper at \"" << gkName << '"' << endl;
      return FALSE;
    }
  }
  else if (!args.HasOption('n') || args.HasOption('r')) {
    cout << "Searching for gatekeeper..." << flush;
    if (h323->DiscoverGatekeeper(new OpalTransportUDP(*h323)))
      cout << "\nGatekeeper found: " << *h323->GetGatekeeper() << endl;
    else {
      cerr << "\nNo gatekeeper found." << endl;
      if (args.HasOption("require-gatekeeper")) 
        return FALSE;
    }
  }

  return TRUE;
}


void MyManager::Main(PArgList & args)
{
  // See if making a call or just listening.
  if (args.HasOption('l'))
    cout << "Waiting for incoming calls\n";
  else {
    cout << "Initiating call to \"" << args[0] << "\"\n";
    SetUpCall("line:*", args[0], currentCallToken);
  }
  cout << "Press X to exit." << endl;

  // Simplest possible user interface
  for (;;) {
    cout << "OPAL> " << flush;
    PCaselessString cmd;
    cin >> cmd;
    if (cmd == "X")
      break;

    // Process commands
  }
}


PString MyManager::OnRouteConnection(OpalConnection & connection)
{
  PString addr = connection.GetDestinationAddress();
  if (addr.IsEmpty())
    return addr;

  if (addr.Find(':') != P_MAX_INDEX)
    return addr;

  if (connection.GetEndPoint().GetPrefixName() != "h323") {
    addr.Replace("*", ".", TRUE);
    return "h323:" + addr;
  }

  if (potsEP != NULL)
    return "pots:" + addr;

  return "pc:" + addr;
}


#if 0
BOOL MyManager::OnIncomingConnection(OpalConnection & connection)
{
  if (currentCallToken.IsEmpty()) {
    currentCallToken = connection.GetToken();

    if (autoAnswer) {
      cout << "Automatically accepting call." << endl;
      return OpalConnection::AnswerCallNow;
    }

    cout << "Incoming call from \""
         << connection.GetRemotePartyName()
         << "\", answer call (Y/n)? "
         << flush;

    return OpalConnection::AnswerCallPending;
  }

  if (busyForwardParty.IsEmpty()) {
    cout << "Incoming call from \"" << connection.GetRemotePartyName() << "\" rejected, line busy!" << endl;
    return OpalConnection::AnswerCallDenied;
  }

  cout << "Forwarding call to \"" << busyForwardParty << "\"." << endl;
  if (connection.ForwardCall(busyForwardParty))
    connection.ClearCall(OpalConnection::EndedByCallForwarded);

  return OpalConnection::AnswerCallDenied;
}
#endif


BOOL MyManager::OnConnectionForwarded(OpalConnection & /*connection*/,
                                      const PString & forwardParty)
{
  cout << "Call is being forwarded to host " << forwardParty << endl;
  return TRUE;
}


void MyManager::OnEstablishedConnection(OpalConnection & connection)
{
  currentCallToken = connection.GetToken();
  cout << "In call with " << connection.GetRemotePartyName() << endl;
}


void MyManager::OnReleasedConnection(OpalConnection & connection)
{
  if (currentCallToken == connection.GetToken())
    currentCallToken = PString();

  PString remoteName = '"' + connection.GetRemotePartyName() + '"';
  switch (connection.GetCallEndReason()) {
    case OpalConnection::EndedByRemoteUser :
      cout << remoteName << " has cleared the call";
      break;
    case OpalConnection::EndedByCallerAbort :
      cout << remoteName << " has stopped calling";
      break;
    case OpalConnection::EndedByRefusal :
      cout << remoteName << " did not accept your call";
      break;
    case OpalConnection::EndedByNoAnswer :
      cout << remoteName << " did not answer your call";
      break;
    case OpalConnection::EndedByTransportFail :
      cout << "Call with " << remoteName << " ended abnormally";
      break;
    case OpalConnection::EndedByCapabilityExchange :
      cout << "Could not find common codec with " << remoteName;
      break;
    case OpalConnection::EndedByNoAccept :
      cout << "Did not accept incoming call from " << remoteName;
      break;
    case OpalConnection::EndedByAnswerDenied :
      cout << "Refused incoming call from " << remoteName;
      break;
    case OpalConnection::EndedByNoUser :
      cout << "Gatekeeper could find user " << remoteName;
      break;
    case OpalConnection::EndedByNoBandwidth :
      cout << "Call to " << remoteName << " aborted, insufficient bandwidth.";
      break;
    case OpalConnection::EndedByUnreachable :
      cout << remoteName << " could not be reached.";
      break;
    case OpalConnection::EndedByNoEndPoint :
      cout << "No phone running for " << remoteName;
      break;
    case OpalConnection::EndedByHostOffline :
      cout << remoteName << " is not online.";
      break;
    case OpalConnection::EndedByConnectFail :
      cout << "Transport error calling " << remoteName;
      break;
    default :
      cout << "Call with " << remoteName << " completed";
  }
  cout << ", duration "
       << setprecision(0) << setw(5)
       << (PTime() - connection.GetConnectionStartTime())
       << endl;
}


BOOL MyManager::OnOpenMediaStream(OpalMediaStream & stream)
{
  if (!MyManager::OnOpenMediaStream(stream))
    return FALSE;

  cout << "Started ";

  if (stream.IsSource())
    cout << "sending ";
  else
    cout << "receiving ";

  cout << stream.GetMediaFormat() << endl;  

  return TRUE;
}



void MyManager::OnUserIndicationString(OpalConnection & connection,
                                       const PString & value)
{
  cout << "User input received: \"" << value << '"' << endl;
  OpalManager::OnUserIndicationString(connection, value);
}


///////////////////////////////////////////////////////////////

MyPCSSEndPoint::MyPCSSEndPoint(MyManager & mgr)
  : OpalPCSSEndPoint(mgr)
{
}


void MyPCSSEndPoint::OnShowRinging(const PString & callerName)
{
  cout << "Call from " << callerName << ", answer? " << flush;
}


BOOL MyPCSSEndPoint::OnShowAlerting(const PString & calleeName)
{
  cout << calleeName << " is ringing ..." << endl;
  return TRUE;
}


BOOL MyPCSSEndPoint::SetSoundDevice(PArgList & args,
                                    const char * optionName,
                                    PSoundChannel::Directions dir)
{
  if (!args.HasOption(optionName))
    return TRUE;

  PString dev = args.GetOptionString(optionName);

  if (dir == PSoundChannel::Player) {
    if (SetSoundChannelPlayDevice(dev))
      return TRUE;
  }
  else {
    if (SetSoundChannelRecordDevice(dev))
      return TRUE;
  }

  cerr << "Device for " << optionName << " (\"" << dev << "\") must be one of:\n";

  PStringArray names = PSoundChannel::GetDeviceNames(dir);
  for (PINDEX i = 0; i < names.GetSize(); i++)
    cerr << "  \"" << names[i] << "\"\n";

  return FALSE;
}


// End of File ///////////////////////////////////////////////////////////////
