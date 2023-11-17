//
// Created by Max Benson on 9/7/2021.
//

#ifndef PERF_H
#define PERF_H

enum PerfType {
    InsertStart,
    InsertEnd,
    RemoveStart,
    RemoveEnd,
    GetStart,
    GetEnd,
    AverageFind,
    AverageGet
};

void TestPerf(PerfType);

#endif //PERF_H
