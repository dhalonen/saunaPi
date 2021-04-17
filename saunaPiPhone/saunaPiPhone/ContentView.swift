//
//  ContentView.swift
//  saunaPiPhone
//
//  Created by David Halonen on 3/12/21.
//

import SwiftUI

struct ContentView: View {
    @StateObject var saunaEnvironment = SaunaEnvironment()
    var body: some View {
        ZStack {
            Text("")
                .frame(maxWidth: .infinity, maxHeight: .infinity)
                .background(Color(.systemBackground))
                .onTapGesture {
                    getSaunaData(saunaEnvironment)
                }
            ReportBlock()
                .onAppear(){
                    print("onAppear")
                    getSaunaData(saunaEnvironment)
                }
                .onReceive(NotificationCenter.default.publisher(for: UIApplication.didBecomeActiveNotification)) { (_) in
                    print("Content View becoming active")
                    getSaunaData(saunaEnvironment)
                }
                .onTapGesture {
                    getSaunaData(saunaEnvironment)
                }
        }
        .background(Color(.systemBackground))
        .environmentObject(saunaEnvironment)
    }
}

func getSaunaData(_ saunaEnvironment: SaunaEnvironment) {
    let url = URL(string: "http://saunapi.harmon/data.json")!
    
    //TODO convert this to async
    let task = URLSession.shared.dataTask(with: url) {(data, response, error) in
        guard let data = data else { return }
        print(String(data: data, encoding: .utf8)!)
        
        let decoder = JSONDecoder()
        do {
            let saunaEnvironmentData = try decoder.decode(SaunaEnvironmentData.self, from: data)
            print(saunaEnvironmentData)
            //We are on a background thread. Need to perform environment object update on main.
            DispatchQueue.main.async {
                saunaEnvironment.temperature = saunaEnvironmentData.temperature
                saunaEnvironment.timeStamp = saunaEnvironmentData.timeStamp
            }
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
        ContentView().preferredColorScheme(/*@START_MENU_TOKEN@*/.dark/*@END_MENU_TOKEN@*/)
    }
}
