//
//  ConnectionControllerViewController.swift
//  carremote
//
//  Created by Sergey Chernov on 1/5/19.
//  Copyright © 2019 Sergey Chernov. All rights reserved.
//

import UIKit
import CoreBluetooth

class ConnectionViewController: UIViewController, CarRemoteDelegate {
    
    
    // MARK: properties
    
    @IBOutlet weak var connStatus: UILabel!
    @IBOutlet weak var speedValue: UILabel!
    

    
    
    
//    @IBAction func turnRight(_ sender: UIButton) {
//        print("turn right");
//        remote?.sendCommand(cmd: [0x02, 0x03])
//    }
    
    @IBAction func turnRight(_ sender: UIButton) {
        print("turn right");
        AppDelegate.remote!.sendCommand(cmd: [0x02, 0x03])
        
    }
    @IBAction func turnLeft(_ sender: UIButton) {
        print("turn left");
        AppDelegate.remote!.sendCommand(cmd: [0x02, 0x09])
    }
    @IBAction func moveForward(_ sender: UIButton) {
        print("move forward");
        AppDelegate.remote!.sendCommand(cmd: [0x02, 0x12])
        
    }
    @IBAction func moveBackward(_ sender: UIButton) {
        print("move backward");
        AppDelegate.remote!.sendCommand(cmd: [0x02, 0x06])
    }
    
    @IBAction func changeSpeed(_ sender: UISlider, forEvent event: UIEvent) {
        print("slide value ", sender.value)
        if (sender.value > 20.0 && sender.value < 256.0) {
            let speed = uint_fast8_t(sender.value)
            speedValue.text = String(format: "%d", speed)
            AppDelegate.remote!.sendCommand(cmd: [0x01, speed])
        }
    }
    
    @IBAction func reconnect(_ sender: UIButton) {
        sender.isEnabled = false
//        connStatus.text = "Connecting"
        print("Reconnecting to device")
        AppDelegate.remote!.start()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        AppDelegate.remote!.delegate = self
    }
    
    override func viewWillAppear(_ animated: Bool) {
//        connStatus.text = "Not connected"
    }
    func connected() {
//        connStatus.text = "Connected"
//        sender.setTitle("Connected", for: .disabled)
    }
    
    func failedToConnect(error: Error?) {
//        connStatus.text = "Failed"
//        sender.setTitle("Connect", for: .normal)
    }
    
    func commandSent() {
        
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
