//
//  ViewController.swift
//  dgdgd
//
//  Created by KOJI KAWAGUCHI on 2020/11/24.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var label: UILabel!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        
        DeployGateSDK.sharedInstance().userAuthorization(completionHandler: { (authorized, error) -> Void in
            
            DispatchQueue.main.async {
            NSLog(authorized ? "Success!!!!!!!!!" : "Failed!!!!!!!!")
            self.label.text = authorized ? "Success!!!!!!!!!" : "Failed!!!!!!!!"
            }
            return
        })

    }


}

