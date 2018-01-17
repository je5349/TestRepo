#include "os5000s_compass/SerialPort.h"
#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <libudev.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

SerialPort::SerialPort():
    fileDesignator(-1),
    portOpen(false)
{
    fileName = "NONE";
}

SerialPort::SerialPort(const char *device, rate baudRate ):
    fileDesignator(-1),
    portOpen(false)
{
    openPort(device, baudRate);
}

SerialPort::SerialPort(std::string device, rate baudRate ):
    fileDesignator(-1),
    portOpen(false)
{
    openPort(device.c_str(), baudRate);
}


//#include <stdio.h>
//#include <usb.h>
//main(){
//    struct usb_bus *bus;
//    struct usb_device *dev;
//    usb_init();
//    usb_find_busses();
//    usb_find_devices();
//    for (bus = usb_busses; bus; bus = bus->next)
//        for (dev = bus->devices; dev; dev = dev->next){
//            printf("Trying device %s/%s\n", bus->dirname, dev->filename);
//            printf("\tID_VENDOR = 0x%04x\n", dev->descriptor.idVendor);
//            printf("\tID_PRODUCT = 0x%04x\n", dev->descriptor.idProduct);
//        }
//}



SerialPort::~SerialPort()
{
    closePort();
}





bool SerialPort::openPort(const char *device, rate baudRate )
{

    if(portOpen)
        closePort();

    fileName = "NONE";

    // open the port
    fileDesignator = open(device, O_RDWR | O_NOCTTY | O_NDELAY);

    // set serial configurations
    //cout << "fileDesignator " << fileDesignator<< endl;

    if(fileDesignator == -1) {
        cout << "Serial Port: failed to open serial device." << endl;
        portOpen = false;
    }
    else {
        // verify that opened device is serial device (aka tty)
        if(!isatty(fileDesignator))
        {
            cout << "Serial Port: this is not a serial device." << endl;
            portOpen = false;
            close(fileDesignator);
            fileDesignator = -1;

        } else {

            struct termios newtio;
            newtio.c_cflag = CS8 | CLOCAL | CREAD ;
            switch( baudRate )
            {
            case  B_0:
                newtio.c_cflag = newtio.c_cflag | B0;
                break;
            case B_50:
                newtio.c_cflag = newtio.c_cflag | B50;
                break;
            case B_75:
                newtio.c_cflag = newtio.c_cflag | B75;
                break;
            case B_110:
                newtio.c_cflag = newtio.c_cflag | B110;
                break;
            case B_134:
                newtio.c_cflag = newtio.c_cflag | B134;
                break;
            case B_150:
                newtio.c_cflag = newtio.c_cflag | B150;
                break;
            case B_200:
                newtio.c_cflag = newtio.c_cflag | B200;
                break;
            case B_300:
                newtio.c_cflag = newtio.c_cflag | B300;
                break;
            case B_600:
                newtio.c_cflag = newtio.c_cflag | B600;
                break;
            case B_1200:
                newtio.c_cflag = newtio.c_cflag | B1200;
                break;
            case B_1800:
                newtio.c_cflag = newtio.c_cflag | B1800;
                break;
            case B_2400:
                newtio.c_cflag = newtio.c_cflag | B2400;
                break;
            case B_4800:
                newtio.c_cflag = newtio.c_cflag | B4800;
                break;
            case B_9600:
                newtio.c_cflag = newtio.c_cflag | B9600;
                break;
            case B_19200:
                newtio.c_cflag = newtio.c_cflag | B19200;
                break;
            case B_38400:
                newtio.c_cflag = newtio.c_cflag | B38400;
                break;
            case B_57600:
                newtio.c_cflag = newtio.c_cflag | B57600;
                break;
            case B_115200:
                newtio.c_cflag = newtio.c_cflag | B115200;
                break;
            case B_230400:
                newtio.c_cflag = newtio.c_cflag | B230400;
                break;
            }

            newtio.c_iflag = IGNPAR | ICRNL;
            newtio.c_oflag = 0;
            newtio.c_lflag = 0; //ICANON; This puts it in connical mode and wates for a new line.
            //newtio.c_cc[VMIN] = 0; // read doesn't block
            //newtio.c_cc[VTIME] = 0;// no timeout seconds read timeout
           // newtio.c_cc[VEOL] = '\n';

            newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */
            newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
            newtio.c_cc[VERASE]   = 0;     /* del */
            newtio.c_cc[VKILL]    = 0;     /* @ */
            newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
            newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
            newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
            newtio.c_cc[VSWTC]    = 0;     /* '\0' */
            newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */
            newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
            newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
            newtio.c_cc[VEOL]     = 0;     /* '\0' */
            newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
            newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
            newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
            newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
            newtio.c_cc[VEOL2]    = 0;     /* '\0' */




            tcflush(fileDesignator, TCIOFLUSH);
            tcsetattr(fileDesignator, TCSAFLUSH, &newtio);

            fileName = string(device);
            portOpen = true;

        }
    }

    return portOpen;
}

void SerialPort::closePort()
{
    if( portOpen )
        close( fileDesignator );

    fileDesignator = -1;
    fileName = "NONE";
    portOpen = false;
}

bool SerialPort::isOpen() const
{
    return fileDesignator !=-1;
}

/**
 * Flushes data buffer for the serial port.
 *
 */
bool SerialPort::flushData( ) {

    if( portOpen )
    {
        ioctl(fileDesignator, TCFLSH, TCIOFLUSH );
    }
    return portOpen; // otherwise
}


/**
 * Reads data from the serial port and puts it in buffer.
 *
 * Function only reads data if data is available within ms_timeout (microsecond resolution)
 *  milli-seconds of the function call.
 *
 * If a start deliminator is specified, it will shift the read data untill startDelim
 *  is found in the input stream and continue reading until the number of specified bytes has
 *  been read after the start deliminator.  If and end deliminator is specified and is not found
 *  after the specified number of bytes has been read the funciton returns -bytes read;
 *
 * Function Returs:
 *   bytes_read if sucessfully completed, should be equal to the number of bytes requested.
 *
 *   0 if serial file is unset (fileDesignaor = -1)
 *
 *  -bytes_read if the specified number of bytes cound not be read beacuse data was not available in specified timout time,
 *   or if the end Deliminator was not achieved.  If a message length of 15 was requested a return of -1 to -14 means the
 *   number was not reached and -15 means that the end deliminator was not achieved.
 *
 */
int SerialPort::readData( char *buffer, int bytes,  double ms_timeout, char startDelim, char endDelim)
{
    if( fileDesignator == -1 )
        return 0; // no input file setup

    int bytes_read = 0;
    bool terminatorFound = false;

    while ( bytes_read < bytes && isDataAvailable( ms_timeout )  && !terminatorFound  )
    {
        int bytes_left = bytes - bytes_read;
        int bytesr = read(fileDesignator, buffer + bytes_read*sizeof(char), bytes_left );
        bytes_read += bytesr;

        // see if start deliminator is start of message
        if( startDelim )
        {
            // find index of start deliminator
            int startIndex = 0;
            for( ; startIndex < bytes_read && buffer[startIndex] != startDelim; startIndex ++ );

            // if not start of message
            if( startIndex > 0 )
            {
                // shift message down to start with start index
                for( int index = 0; index < (bytes_read-startIndex); index ++ )
                    buffer[index] = buffer[index+startIndex];

                for( int index = bytes_read-startIndex; index < bytes_read; index ++ )
                    buffer[index] = 0;

                // reduce effective number of bytes read
                bytes_read -= startIndex;
            }
        }

        // Check to see if we found the terminator (if there is one specified)
        if( endDelim  )
            terminatorFound = endDelim == buffer[bytes_read-1]; // check to see if we found the termination character
        else if( bytes_read >= bytes )
            terminatorFound = true;
    }


    // If less than the number of bytes requested were read AND either there was no end deliminator or the end deliminator did not match then negate the result.
    if( ((bytes_read < bytes) && endDelim == 0) || (endDelim !=0 && endDelim != buffer[bytes_read-1]) )
        return -bytes_read; // did not complete task as desired or did not end with end deliminator
    return bytes_read;
}

unsigned char SerialPort::readByte(double ms_timout)
{
    char buf[1] = {0};
    readData( buf, 1, ms_timout);
    return buf[0];
}

std::string SerialPort::getLine( char endDelim )
{
    std::string returnString;

    int numRead = -1;
    while( numRead < 0 )
    {
        char buf[512] = {0};
        numRead = readData(buf, sizeof(buf), 50, 0, endDelim);
        returnString.append(buf);
    }
    return returnString;
}

bool SerialPort::writeData( const char* buffer, int bytes)
{
    int bytesWritten = 0;
    if( fileDesignator !=-1 )
    {
        bytesWritten = write(fileDesignator, buffer, bytes);
    }
    //cout << "wrote " << bytesWritten << endl;
    return bytesWritten == bytes;
}

bool SerialPort::writeByte( char byteToWrite )
{
    return writeData( &byteToWrite, sizeof(char));
}

bool SerialPort::writeString(const std::string& data )
{
   // cout << sizeof(data.c_str()) << " " << data.length() << endl;
    bool retVal = writeData( data.c_str(), data.length() );
    return retVal;
}


bool SerialPort::isDataAvailable( double ms_timeout )
{
    tv.tv_sec  = (int)ms_timeout/1000;
    tv.tv_usec = (ms_timeout-1000*tv.tv_sec)*1000;

    FD_ZERO(&rfds);
    FD_SET(fileDesignator,&rfds);

    int retval = select(fileDesignator+1, &rfds, NULL, NULL, &tv);


    if( retval == -1 )
        cout << "Error occured in isDataAvailable Serial Port Call to " << fileName << endl;

    return (retval > 0);
}

vector<SerialPort::DeviceInfo> SerialPort::getDevPath(string vendorID, string productID){
    struct udev *udev = NULL;
    struct udev_enumerate *enumerate = NULL;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev, *devParent;
    vector<DeviceInfo> answer;

    udev = udev_new();
    assert(('Cant create udev',udev));

    if (!udev) 
    {
        //printf("Can't create udev\n");
		return answer;	
	}

    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "tty");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);

    dev_list_entry  = 0;
    udev_list_entry_foreach(dev_list_entry, devices)
    {
        const char *path;
        path = udev_list_entry_get_name(dev_list_entry);

        dev = udev_device_new_from_syspath(udev, path); // this is the tty file
       // cout << udev_device_get_devnode(dev) << endl;
        devParent = udev_device_get_parent_with_subsystem_devtype( dev, "usb", "usb_device"); // this is the parent device
       // cout << udev_device_get_devnode(devParent) << endl;

        if (!devParent || !dev)
        {
            //printf("Unable to find parent usb device.");
            continue;
            //exit(1);
        }

        if (vendorID.compare((udev_device_get_sysattr_value(devParent,"idVendor")))==0 &&
                productID.compare((udev_device_get_sysattr_value(devParent, "idProduct")))==0)
        {
            //printf("Device Found!\n");
            //printf("%s\n",udev_device_get_sysattr_value(dev,"manufacturer") );
            /* Free the enumerator object */

            DeviceInfo newDevice;

            newDevice.filePath = udev_device_get_devnode(dev);
            newDevice.manufacturer = udev_device_get_sysattr_value(devParent,"manufacturer");
            newDevice.product = udev_device_get_sysattr_value(devParent,"product");
            newDevice.serial = udev_device_get_sysattr_value(devParent,"serial");

            answer.push_back(newDevice); // push back teh tty path
            
        }
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    // Return empty string if nothing is found...
    return answer;
}
