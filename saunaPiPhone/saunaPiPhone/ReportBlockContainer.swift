//
//  ReportBlockContainer.swift
//  saunaPiPhone
//
//  Created by David Halonen on 4/16/21.
//

import SwiftUI

struct ReportBlockContainer: View {
    @EnvironmentObject var saunaEnvironment: SaunaEnvironment
    /*
     Temp range = 185 - 65 = 120 deg F
     ratio = geo.size.height / 120 = ht/deg
     offset = max height - deg * ratio 
     */
    let blockSize: CGFloat = 70 //need to get actual size
    let topReportBlockPadding: CGFloat = 30
    var body: some View {
        GeometryReader { geo in
            ReportBlock()
                .offset(y: saunaEnvironment.computeOffset(height: geo.size.height) - blockSize + topReportBlockPadding
                )
        }
    }
}

struct ReportBlockContainer_Previews: PreviewProvider {
    static let zero = 0
    static var previews: some View {
        Group {
            VStack {
                ReportBlockContainer().environmentObject(
                    SaunaEnvironment(temperature: 145,
                                     timeStamp: "right now!"))
            }
        }
    }
}
