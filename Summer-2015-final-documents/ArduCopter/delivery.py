"""
delivery.py: GUIDED mode "delivery" example 
The code demonstrates how to arm and takeoff in Copter and how to navigate to 
points using Vehicle.commands.goto.
"""

import time
from droneapi.lib import VehicleMode, Location
from pymavlink import mavutil

# First get an instance of the API endpoint
api = local_connect()
# Get the connected vehicle (currently only one vehicle can be returned).
drone = api.get_vehicles()[0]

print " Location: %s" % drone.location

print

def arm_and_takeoff(aTargetAltitude):
    """
    Arms vehicle and fly to aTargetAltitude(meters).
    """
    
    print "Basic pre-arm checks"
    # Don't let the user try to fly autopilot is booting
    if drone.mode.name == "INITIALISING":
        print "Waiting for vehicle to initialise"
        time.sleep(1)
    
    while drone.gps_0.fix_type < 2:
        print "Waiting for GPS...:", vehicle.gps_0.fix_type
        time.sleep(1)
		
    print "Arming motors"
    # Copter should arm in GUIDED mode
    drone.mode    = VehicleMode("GUIDED")
    drone.armed   = True
    drone.flush()

    while not drone.armed and not api.exit:
        print " Waiting for arming..."
        time.sleep(1)

    print "Taking off!"
    drone.commands.takeoff(aTargetAltitude) # Take off to target altitude
    drone.flush()

    # Wait until the vehicle reaches a safe height before processing the goto (otherwise the command 
    #  after Vehicle.commands.takeoff will execute immediately).
    while not api.exit:
        print " Altitude: ", drone.location.alt
#        print " Atiltude que eu quero: ", aTargetAltitude
        if drone.location.alt >= aTargetAltitude*0.95: #Just below target, in case of undershoot.
            print "Reached target altitude: %s" %(drone.location.alt)
            break;
        time.sleep(1)

def get_location():
    return [drone.location.lat, drone.location.lon]

def goto_waypoint(location, altitude):
    point = Location(location[0], location[1], altitude, is_relative=True)
    drone.commands.goto(point)
    time.sleep(10)
    drone.flush()
    
#    while not api.exit:
#        print "Location: ", get_location()
#        if drone.location.lat == location[0] and drone.location.lon == location[1]:
#            print "Reached target location: %s" %(get_location())
#            break;
#        time.sleep(1)

def land_mode():
    print("Setting LAND mode...")
    drone.mode = VehicleMode("LAND")
    time.sleep(30)# LANDING TIME DON'T TOUCH THIS
    drone.flush()
    
    print " Waiting for landing..."
    while not drone.mode.name =='LAND' and not api.exit:
        print " Waiting for landing..."
        print " Altitude: ", drone.location.alt
        if drone.location.alt <= 0.3: # 
            print "Landed at: %s" %(drone.location.alt)
            break;
        time.sleep(1)
        
def take_off(aTargetAltitude):
    print "Arming motors"
    # Copter should arm in GUIDED mode
    drone.mode    = VehicleMode("GUIDED")
    drone.armed   = True
    drone.flush()

    while not drone.armed and not api.exit:
        print " Waiting for arming..."
        time.sleep(1)

    print "Taking off!"
    drone.commands.takeoff(aTargetAltitude) # Take off to target altitude
    drone.flush()

    # Wait until the vehicle reaches a safe height before processing the goto (otherwise the command 
    #  after Vehicle.commands.takeoff will execute immediately).
    while not api.exit:
        print " Altitude: ", drone.location.alt
        if drone.location.alt >= aTargetAltitude*0.95: #Just below target, in case of undershoot.
            print "Reached target altitude: %s" %(drone.location.alt)
            break;
        time.sleep(1)
 
alt = 10

arm_and_takeoff(alt)
   
print "Going to first point..."
lat = 41.8401671
lon = -87.6246947
goto_waypoint([lat, lon], alt)
time.sleep(1)

print "Going to second point..."
goto_waypoint([lat, lon], 2)
time.sleep(2)

#land_mode()

#take_off(5)

# Returning to Launch
print "Returning to Launch"
drone.mode    = VehicleMode("RTL")
time.sleep(10)
drone.flush()
    
print "Complete"


















#
#



#take_off()

# Returning to Launch
#print "Returning to Launch"
#drone.mode    = VehicleMode("RTL")
#time.sleep(10)
#drone.flush()


#print("Setting LAND mode...")
#drone.mode = VehicleMode("LAND")
#time.sleep(300)# LANDING TIME DON'T TOUCH THIS
#drone.flush()


#drone.armed = False
#drone.flush()



