//
//  ReportBlock.swift
//  saunaPiPhone
//
//  Created by David Halonen on 3/12/21.
//

import SwiftUI

struct ReportBlock: View {

    @Environment(\.colorScheme) var envColorScheme
    @EnvironmentObject var saunaEnvironment: SaunaEnvironment
    var body: some View {
            ZStack {
                    HStack {
                        Text(String(saunaEnvironment.temperature ?? 65))
                            .bold()
                            .font(.system(size: 40))
                            .padding(4)
                            .foregroundColor(saunaEnvironment.temperatureColor)
                            .opacity(hideTemp(saunaEnvironment.temperature!))
                        Spacer()
                    }
                    HStack {
                        Spacer()
                        Text(saunaEnvironment.timeStamp ?? "Missing data")
                            .padding(.trailing, 4)
                            .foregroundColor(Color(.label))
                        
                    }
            }

        .onAppear(){
            print("onAppear")
            getSaunaData(saunaEnvironment)
        }
        .onReceive(NotificationCenter.default.publisher(for: UIApplication.didBecomeActiveNotification)) { (_) in
            print("Content View becoming active")
            getSaunaData(saunaEnvironment)
        }
    }

    func hideTemp(_ temp: Int) -> Double {
        return temp == 0 ? 0.0 : 1.0
    }
}

struct ReportBlock_Previews: PreviewProvider {
    static let zero = 0
    static var previews: some View {
        Group {
            VStack {
                ReportBlock().environmentObject(
                    SaunaEnvironment(temperature: zero,
                                     timeStamp: "right now!"))
                ReportBlock().environmentObject(
                    SaunaEnvironment(temperature: 65,
                                     timeStamp: "right now!"))
                ReportBlock().environmentObject(
                    SaunaEnvironment(temperature: 99,
                                     timeStamp: "right now!"))
                ReportBlock().environmentObject(
                    SaunaEnvironment(temperature: 135,
                                     timeStamp: "right now2!"))
                ReportBlock().environmentObject(
                    SaunaEnvironment(temperature: 165,
                                     timeStamp: "right now3!"))
            }.environment(\.colorScheme, .dark)
            VStack {
                ReportBlock().environmentObject(
                    SaunaEnvironment(temperature: zero,
                                     timeStamp: "right now!"))
                ReportBlock().environmentObject(
                    SaunaEnvironment(temperature: 65,
                                     timeStamp: "right now!"))
                ReportBlock().environmentObject(
                    SaunaEnvironment(temperature: 99,
                                     timeStamp: "right now!"))
                ReportBlock().environmentObject(
                    SaunaEnvironment(temperature: 135,
                                     timeStamp: "right now2!"))
                ReportBlock().environmentObject(
                    SaunaEnvironment(temperature: 165,
                                     timeStamp: "right now3!"))
            }.environment(\.colorScheme, .light)
        }
    }
}
