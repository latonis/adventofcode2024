import Foundation

func read_file(dir: String) -> String {
    do {
        let input = try String(
            contentsOfFile: dir, encoding: String.Encoding.utf8)
        return input
    } catch {
        NSLog("Failed to read in the input file")
    }
    return ""
}

func part_one(dir: String) {
    var fs = [Int]()
    var ss = [Int]()
    read_file(dir: dir).components(separatedBy: "\n").forEach {
        let entries = $0.components(separatedBy: "   ").map {
            let i: Int? = Int($0.trimmingCharacters(in: .whitespacesAndNewlines))
            return i
        }
        fs.insert(
            entries[0] ?? 0, at: fs.firstIndex(where: { entries[0] ?? 0 < $0 }) ?? fs.endIndex)
        ss.insert(
            entries[1] ?? 0, at: ss.firstIndex(where: { entries[1] ?? 0 < $0 }) ?? ss.endIndex)
    }

    print(zip(fs, ss).map({ abs($0 - $1) }).reduce(0, +))
}

func part_two(dir: String) {
    var fs = [Int]()
    var ss = [Int: Int]()

    read_file(dir: dir).components(separatedBy: "\n").forEach {
        let entries = $0.components(separatedBy: "   ").map {
            let i: Int? = Int($0.trimmingCharacters(in: .whitespacesAndNewlines))
            return i
        }
        fs.insert(
            entries[0] ?? 0, at: fs.firstIndex(where: { entries[0] ?? 0 < $0 }) ?? fs.endIndex)
        ss[entries[1] ?? 0, default: 0] += 1
    }

    print(fs.map({ $0 * ss[$0, default: 0] }).reduce(0, +))

}

part_one(dir: "./input")
part_two(dir: "./input")
