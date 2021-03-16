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
            ReportBlock(saunaEnvironment: SaunaEnvironment())
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
        
        let decoder = JSONDecoder()
        do {
            let saunaEnvironmentData = try decoder.decode(SaunaEnvironmentData.self, from: data)
            print(saunaEnvironmentData)
        } catch {
            print(error)
        }
    }
    
    task.resume()
}

struct SaunaEnvironmentData: Codable {
    var temperature: Int
    var timeStamp: String
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
