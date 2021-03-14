//
//  ContentView.swift
//  saunaPiPhone
//
//  Created by David Halonen on 3/12/21.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        ZStack {
            Text("")
                .frame(maxWidth: .infinity, maxHeight: .infinity)
                .background(Color.white)
                .onTapGesture {
                    getSaunaData()
                }
            ReportBlock(temperature: "120", timeStamp: "3/7/62")
                .onTapGesture {
                    getSaunaData()
                }
        }
    }
}

func getSaunaData() {
    let url = URL(string: "http://saunapi.harmon/data.json")!
    
    let task = URLSession.shared.dataTask(with: url) {(data, response, error) in
        guard let data = data else { return }
        print(String(data: data, encoding: .utf8)!)
    }
    
    task.resume()
}
struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
