//
//  ReportBlock.swift
//  saunaPiPhone
//
//  Created by David Halonen on 3/12/21.
//

import SwiftUI

struct ReportBlock: View {
    //    var temperature: String
    //    var timeStamp: String
    @StateObject var saunaEnvironment: SaunaEnvironment
    var body: some View {
        VStack(alignment: .leading) {
            ZStack {
                VStack(alignment: .leading){
                    HStack {
                        Text(String(saunaEnvironment.temperature ?? 65))
                            .bold()
                            .font(.system(size: 40))
                            .padding(4)
                            .foregroundColor(saunaEnvironment.temperatureColor)
                        Spacer()
                    }
                }
                VStack(alignment: .trailing) {
                    HStack {
                        Spacer()
                        Text(saunaEnvironment.timeStamp ?? "Missing data")
                            .padding(.trailing, 4)
                    }
                }
                .offset(x: 0, y: 10)
            }
            
        }
        //  .frame(width: .infinity)
        
    }
}

struct ReportBlock_Previews: PreviewProvider {
    static var previews: some View {
        VStack {
            ReportBlock(saunaEnvironment:
                            SaunaEnvironment(temperature: 60,
                                             timeStamp: "right now!"))
            ReportBlock(saunaEnvironment:
                            SaunaEnvironment(temperature: 99,
                                             timeStamp: "right now!"))
            ReportBlock(saunaEnvironment:
                            SaunaEnvironment(temperature: 135,
                                             timeStamp: "right now2!"))
            ReportBlock(saunaEnvironment:
                            SaunaEnvironment(temperature: 165,
                                             timeStamp: "right now3!"))
        }
    }
}
