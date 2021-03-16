//
//  SaunaEnvironment.swift
//  saunaPiPhone
//
//  Created by David Halonen on 3/15/21.
//

import SwiftUI

class SaunaEnvironment: ObservableObject {
    @Published var temperature: Int?
    @Published var timeStamp: String?
    
    init(temperature: Int = 65, timeStamp: String = "January 1, 1970 7:00 PM EST") {
        self.temperature = temperature
        self.timeStamp = timeStamp
    }
    
    var temperatureColor: Color {
        guard let temp = self.temperature else {
            return .blue
        }
        switch temp {
        case ..<90:
            return .blue
        case ..<129:
            return .green
        case ..<149:
            print("orange")
            return .orange
        default:
            return .red
        }
    }
}
