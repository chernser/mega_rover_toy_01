//
//  CarRemote.swift
//  carremote
//
//  Created by Sergey Chernov on 1/30/19.
//  Copyright © 2019 Sergey Chernov. All rights reserved.
//

import Foundation
import CoreBluetooth

public protocol CarRemoteDelegate : NSObjectProtocol {
    
//    optional public func peripheralDidUpdateName(_ peripheral: CBPeripheral)
    func connected()
    
    func failedToConnect(error: Error?)
    
    func commandSent()

}

class CarRemote: NSObject, CBCentralManagerDelegate, CBPeripheralDelegate {
    
    private final let SERVICE_UUID = CBUUID(string: "FFE0")
    private final let CMD_CHARACTERISTIC_UUID = CBUUID(string: "FFE1")
    private var bleManager: CBCentralManager?
    private var remoteDevice:CBPeripheral?
    private final let serviceUUID:CBUUID!
    public var delegate:CarRemoteDelegate?
    
    override init() {
        self.serviceUUID = SERVICE_UUID
        
    }
    
    
    init(delegate:CarRemoteDelegate, deviceUUID:String) {
        self.serviceUUID = CBUUID(string: deviceUUID)
    }
    
    public func start() {
        if (remoteDevice != nil ) {
            remoteDevice = nil
        }
        if (bleManager == nil) {
            bleManager = CBCentralManager(delegate: self, queue: nil)
        }
    }
    
    private func scan() {
    }
    
    // --------  Central manager delegate impl
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        print("State update: ", central.state)
        if central.state == CBManagerState.poweredOn {
            print("Started scan")
            let options: [String: Any] = [CBCentralManagerScanOptionAllowDuplicatesKey:NSNumber(value: false)]
            bleManager?.scanForPeripherals(withServices: [serviceUUID], options: options)
        }
    }
    
    //Finds peripheral and connects to it
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        print("Found device ", peripheral.name)
        bleManager?.stopScan()
        remoteDevice = peripheral
        remoteDevice?.delegate = self
        bleManager?.connect(peripheral, options: nil)
        print("Scan stopped. Peripheral connecting...")
    }
    
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        print("Connected")
        delegate?.connected()
        remoteDevice?.discoverServices([serviceUUID])
    }

    func centralManager(_ central: CBCentralManager, didFailToConnect peripheral: CBPeripheral, error: Error?) {
        print("Failed to connect", error)
        delegate?.failedToConnect(error: error)
    }
    
    // ------- CBPeripheral delegate impl
    
    // Find service first
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        for service in remoteDevice!.services! {
            if service.uuid == serviceUUID {
                remoteDevice?.discoverCharacteristics(nil, for: service)
                break
            }
        }
    }

    private var cmdCharacteristic:CBCharacteristic?

    // Find characteristics for service then
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        for char in service.characteristics! {
            if char.uuid == CMD_CHARACTERISTIC_UUID {
                cmdCharacteristic = char
//                peripheral.discoverDescriptors(for: cmdCharacteristic)
                break
            }
        }
    }
    
    // ----------- end of delegate impl
    
    
    public func sendCommand(cmd: [UInt8]) {
        if cmdCharacteristic == nil {
            print("Characteristic is nil")
            return
        }
        
        print("Sending command ", cmd)
        var data:Data = Data.init(count: cmd.count)
        data.append(contentsOf: cmd)
//        let desc:CBDescriptor?
        
        remoteDevice?.writeValue(data, for: cmdCharacteristic!, type: CBCharacteristicWriteType.withoutResponse )
        delegate?.commandSent()
        print("Command sent: ", cmd)
    }
    
    public func stop() {
        if (remoteDevice != nil && bleManager != nil) {
            bleManager!.cancelPeripheralConnection(remoteDevice!)
        }
        remoteDevice = nil
        
        if (bleManager != nil) {
            bleManager!.stopScan()
            bleManager = nil
        }
    }
}
