% ----------------------------------------------------
% Illinois Institute of Technology
% ITMT 492 - Embedded Systems
%
% Students: Igor de Sousa Dantas,
%			Leonardo Pavanatto Soares,
% 			Nicolas Ribeiro Vieira,
%			Pedro Henrique de Brito Souza,
% 			Rodrigo Moreno Garcia.
% 
% Instructors: Dr Daniel Tomal,
%			   Jeremy Hajek.
%
% Project: O.Y.T. - The Track Guided Robot
% File: Matlab Central Command
% Last Modified: May 5, 2015
% ----------------------------------------------------

clear all; close all; clc; 
delete(instrfind); %delete serial port if any exist
isConnected = false;
goodConnect = false;
numberSamples = 500;
isThereData = false;
myTime = 0.001;
choice = 0;
portFP = 0;
while(choice < 5) %while used by the menu options
   choice = menu('Select an option',...
                 'Connect to O.Y.T. System',...
                 'START O.Y.T.',...
                 'STOP O.Y.T.',...
                 'Read Data O.Y.T.',...
                 'EXIT Application'); 
   switch(choice)
       case 1 %set up communication with Arduino
           if(portFP)
               msgbox('The monitoring system is already connected!');
           else
               portNum = 'COM4'; %Default serial port (Windows)
               baudRate = 9600; % Communication speed
               %inputdlg used by the user for setting up port and boundrate
               vals = inputdlg({'COM Port: ', 'Baud Rate: '},...
                                'Connection Parameters', 1,...
                                {portNum, num2str(baudRate)});
               portNum = vals{1};
               baudRate = str2num(vals{2});
               portFP = serial(portNum, 'BaudRate', baudRate); %Serial communication (Arduino) is set up using the user or default options
               set(portFP,'DataBits', 8);
               set(portFP,'StopBits', 1);
               isConnected = true;
               if(exist('portFP')) %Check if the communication exists
                   fopen(portFP); %open the port before use it
                   if(strcmp(portFP.Status, 'open'))
                       msgbox('The monitoring system is connected!');
                       goodConnect = true; %flag variable used by other switch cases
                   else
                       goodConnect = false;
                       msgbox('The connection failed!')
                   end
               end
           end
           
       case 2
           if(goodConnect)
               fwrite(portFP, '1');
               
           end
           
       case 3
           if(goodConnect)
               fwrite(portFP, '0');
           end
       case 4
           while(portFP.BytesAvailable>0)
               fscanf(portFP)
           end

   end
end
   
portFP
if(isConnected)
    if(exist('portFP') && strcmp(portFP.status, 'open')) %if there is a connection and it is open, close before exit the program
        fclose(portFP) %close port connection
    end
    instrList = instrfind; %delete the serial port connection used by this program
    if(length(instrList))
        delete(instrList);
    end
end
   close all; %close all plots