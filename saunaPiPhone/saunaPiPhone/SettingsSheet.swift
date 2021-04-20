//
//  SettingsSheet.swift
//  saunaPiPhone
//
//  Created by David Halonen on 4/19/21.
//

import SwiftUI

struct SettingSheet: View {
    @Environment(\.presentationMode) var presentationMode
    
    var body: some View {
        Text("This is it")
        Button("Dismiss") {
            self.presentationMode.wrappedValue.dismiss()
        }
    }
}
