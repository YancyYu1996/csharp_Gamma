using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.InteropServices;
using System.IO.Ports;

namespace MyDll
{
    public class VitualUSB
    {
   

        [DllImport("SiUSBXp.dll", SetLastError = true)]
        public static extern byte SI_GetNumDevices(int lpwdNumDevices);
        [DllImport("SiUSBXp.dll", SetLastError = true)]
        public static extern byte SI_GetProductString(int DdwDeviceNumevNum,  byte lpvDeviceString, int dwFlags);
        [DllImport("SiUSBXp.dll", SetLastError = true)]
        public static extern byte SI_Open( uint dwDevice,  uint cyHandle);
        [DllImport("SiUSBXp.dll", SetLastError = true)]
        public static extern byte SI_Close( uint cyHandle);
        [DllImport("SiUSBXp.dll", SetLastError = true)]
        public static extern byte SI_Read( uint cyHandle,  Byte lpBuffer,  int dwBytesToRead,  int lpdwBytesReturned,  int lpOverlapped);
        [DllImport("SiUSBXp.dll", SetLastError = true)]
        public static extern byte SI_Write( uint cyHandle,  Byte lpBuffer,  int dwBytesToWrite,  int lpdwBytesWritten,  int lpOverlapped);
        [DllImport("SiUSBXp.dll", SetLastError = true)]
        public static extern byte SI_SetTimeouts( int dwReadTimeout,  int dwWriteTimeout);
        [DllImport("SiUSBXp.dll", SetLastError = true)]
        public static extern byte SI_GetTimeouts( int lpdwReadTimeout,  int lpdwWriteTimeout);
        [DllImport("SiUSBXp.dll", SetLastError = true)]
        public static extern byte SI_CheckRXQueue( uint cyHandle,  uint lpdwNumBytesInQueue,  uint lpdwQueueStatus);

        public void Comm_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            throw new NotImplementedException();
        }

        public void DispUI(byte[] InputBuf)
        {
            throw new NotImplementedException();
        }


        //'Masks for the serial number and description
        public const byte SI_RETURN_SERIAL_NUMBER = 0x0;
        public const byte SI_RETURN_DESCRIPTION = 0x1;

        //Masks for return values from the device
        public const byte SI_SUCCESS = 0x0;
        public const byte SI_DEVICE_NOT_FOUND = 0xFF;
        public const byte SI_INVALID_HANDLE = 0x1;
        public const byte SI_READ_ERROR = 0x2;
        public const byte SI_RX_QUEUE_NOT_READY = 0x3;
        public const byte SI_WRITE_ERROR = 0x4;
        public const byte SI_RESET_ERROR = 0x5;
        public const byte SI_INVALID_BUFFER = 0x6;
        public const byte SI_INVALID_REQUEST_LENGTH = 0x7;
        public const byte SI_DEVICE_IO_FAILED = 0x8;

        public const byte SI_QUEUE_NO_OVERRUN = 0x0;
        public const byte SI_QUEUE_OVERRUN = 0x1;
        public const byte SI_QUEUE_READY = 0x2;

        public const short SI_MAX_DEVICE_STRLEN = 256;
        public const short SI_MAX_READ_SIZE = 64;
        public const short SI_MAX_WRITE_SIZE = 64;

        static public string path1 = System.Environment.CurrentDirectory;
        static public string defaultPath = Win32API.INIGetStringValue(path1 + "INI.ini", "INI", "defaultPath", null);




    }
}
