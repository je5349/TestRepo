#include "os5000s_compass/compass.h"
#include <string>
#include <sstream>



bool Compass::loop( double  )
{
    char buffer[1024];
    memset(buffer,0,1024);

    string sentence(last_tail);
    if( myPort.isOpen() )
    {
        //sentence = myPort.getLine('\r\n');
        int numRead = myPort.readData(buffer,1024,1,0,0);

        if( numRead == 0 )
            return true; // nothing to do

      //  cout << "Read: "<< numRead << " Message: \n" << buffer << endl << "----End of Buffer----\n";


        sentence.append(buffer);
        last_tail = "";

   //     cout << sentence << "\n------End of Sentence------\n"<< endl;

        std::stringstream input(sentence);

        int totalLength = sentence.length();


        while( input.good() )
        {
            switch (input.get()) // get a character
            {
            case '$':
            {
                // check length remaining
               // cout << " Position: " << input.tellg() << " length: " << totalLength << " diff " << (totalLength - input.tellg()) << endl;

                if( (totalLength - input.tellg()) < 100 )
                {
                    // if long enough continue
                    // if too short put it all in last_tail and return true

                    // we have a truncated message
                    input.unget(); // put the $ back
                    getline(input,last_tail); // put the rest of the message in last_tail
               //     cout << " Position: " << input.tellg() << " length: " << totalLength << "  good? " << input.good() << endl;
               //     cout << " Last Tail: " << last_tail << endl; // help with debug
                }
                break;
            }
            case 'C':
                input >> heading;
                break;
            case 'P':
                input >> pitch;
                break;
            case 'R':
                input >> roll;
                break;
            case 'T':
                input >> temperature;
                break;
            case 'D':
                input >> depth;
                break;
            case '*':
                for( int i=0; i<2 && input.good(); i++)
                    input.get();// get checksum hex
                break;
            case 'M':
            {
                switch(input.get())
                {
                case 'x':
                    input >> Mx;
                    break;
                case 'y':
                    input >> My;
                    break;
                case 'z':
                    input >> Mz;
                    break;
                default:
                    input.unget();
                    input >> magnetic_vector_length;
                    break;
                }
                break;
            }
            case 'A':
            {
                switch(input.get())
                {
                case 'x':
                    input >> Ax;
                    break;
                case 'y':
                    input >> Ay;
                    break;
                case 'z':
                    input >> Az;
                    break;
                default:
                    input.unget();
                    input >> acceleration_vector_length;
                    break;
                }
                break;
            }

            default:
            {
                break;
            }

            }// end outer switch


        } // end while loop

    } else
    {
        return 0; // because port is closed
    } // end if is opened

    // Output assignments for testing purposes. Comment out as required.
   /* std::cout << "Head: " << heading << "\n"
              << "Pitch" << pitch << "\n"
              << "Roll: " << roll << "\n"
              << "Temperature: " << temperature << "\n"
              << "Depth: " << depth << "\n"
              << "Magnetic Vector Length: " << magnetic_vector_length << "\n"
              << "Mx: " << Mx << "\n"
              << "My: " << My << "\n"
              << "Mz: " << Mz << "\n"
              << "Acceleration Vector Length: " << acceleration_vector_length << "\n"
              << "Ax: " << Ax << "\n"
              << "Ay: " << Ay << "\n"
              << "Az: " << Az << "\n"
              << "\n------End of Parsing------\n";
   */

    return true;
}

Compass::Compass()
{
    std::vector<SerialPort::DeviceInfo> portList = SerialPort::getDevPath("0403","6001");//SerialPort::getDevPath("067b","2303");

    for( int i=0; i<portList.size();i++)
        std::cout << "Expected Port: " << portList[i].filePath << "\tproduct\t" << portList[i].product << endl;

    for( int i=0; i< portList.size(); i++ )
    {
        if( portList[i].product.compare("UC232R") == 0 )
        {
            myPort.openPort(portList[i].filePath.c_str(),SerialPort::B_57600);
            std::cout << "Connecting to Port: " << portList[i].filePath << endl;
            break;
        }
    }

    //myPort.openPort("/dev/ttyUSB0",myPort.B_57600);

    /////////////////////////////////
    // Initialize Compass Settings //
    /////////////////////////////////

    // Change to Format 1
    std::string message = "\e*";
    myPort.flushData();
    myPort.writeString(message);
    message = myPort.getLine(0);
    message = "1\r";	// Set to desired setting here
    myPort.writeString(message);
    Timing::Timer::wait(100);

    /*	Settings for Average filter
              Enter value between 1 to 16.
              See Moving  average  filter  on  roll,  pitch  and  heading.
              Enter  the  number  of samples to include in the average.
              This combined with output rate will determine the period of the filter.
              Example: averaging = 5 output rate = 10 is half second period */
    message = "\eA";
    myPort.flushData();
    myPort.writeString(message);
    message = myPort.getLine(0);
    message = "1\r";	// Set to desired setting here
    myPort.writeString(message);
    Timing::Timer::wait(100);

    /*	Settings for Analog to Digital Converter Decimation Filter
              1: 470 Hz, 4ms settling time
              2: 242 Hz, 8ms settling time
              3: 123 Hz, 15 ms settling time (factory default)
              4: 62 Hz, 32 ms settling time
              5: 50 Hz, 40 ms settling time
              6: 39 Hz, 48 ms settling time
              7: 33.2 Hz, 60 ms settling time
              8: 19.6 Hz, 101 ms settling time, 90 dB rejection of 60Hz noise
              9: 16.7 Hz, 120 ms settling time, 90 dB rejection of 50Hz noise   */
    message = "\eD";
    myPort.flushData();
    myPort.writeString(message);
    message = myPort.getLine(0);
    message = "2\r"; 	// Set to desired setting here
    myPort.writeString(message);
    Timing::Timer::wait(250);

    /*	Settings for Compass Output Rate
              Enter value between -50 to +40.
              Rate is in samples per second and Negative  are  seconds  per  sample.
              (i.e. 20=20  samples/second, -10=10  seconds  per  sample.)
              A  rate  of  0  will  stop  output.
              Note: At  higher output rates the baud rate will need to be increase beyond the standard setting. */
    message = "\eR";
    myPort.flushData();
    myPort.writeString(message);
    message = myPort.getLine(0);
    message = "40\r";	// Set to desired setting here
    myPort.writeString(message);

    ////////////////////////////////////////////
    // Initialize Loop Rate for ROS Node Here //
    ////////////////////////////////////////////

    myPort.flushData();
    this->start( 80 ); // run at 40 hz

    // Empty old messages that were sent while we did the setup
    myPort.flushData();
    last_tail = "";
}

Compass::~Compass()
{
    this->stop();
}

double Compass::getHeading()
{
    return heading;
}

double Compass::getPitch()
{
    return pitch;
}

double Compass::getRoll()
{
    return roll;
}

double Compass::getTemperature()
{
    return temperature;
}

double Compass::getDepth()
{
    return depth;
}

double Compass::getMagneticVectorLength()
{
    return magnetic_vector_length;
}

double Compass::getMx()
{
    return Mx;
}

double Compass::getMy()
{
    return My;
}

double Compass::getMz()
{
    return Mz;
}

double Compass::getAccelerationVectorLength()
{
    return acceleration_vector_length;
}
double Compass::getAx()
{
    return Ax;
}

double Compass::getAy()
{
    return Ay;
}

double Compass::getAz()
{
    return Az;
}


