//
//  SettingsView.swift
//  saunaPiPhone
//
//  Created by David Halonen on 4/19/21.
//

import SwiftUI

struct SettingsControl: View {
    @Binding var settingsSheet: Bool
    
    var body: some View {
        HStack(alignment: .top) {
            Spacer()
            Button(action: {
                self.settingsSheet.toggle()
            }) {
                Image(systemName: "gear")
                    .resizable()
                    .frame(width: 25, height: 25)
           }
            .padding(.top, 5)
            .padding(.trailing, 5)
        }
    }
}

struct SettingsView_Previews: PreviewProvider {
    @State static var settingsSheet = false
    static var previews: some View {
        VStack {
        SettingsControl(settingsSheet: $settingsSheet)
            .previewDevice("iPhone SE (2nd generation)")
        Spacer()
        }
    }
}
