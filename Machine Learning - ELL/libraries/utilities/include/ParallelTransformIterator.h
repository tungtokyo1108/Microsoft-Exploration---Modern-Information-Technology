/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/ParallelTransformIterator.h
 *
 *  Created on: Jan 16, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

#include <future>
#include <thread>
#include <vector>

#define DEFAULT_MAX_TASKS 8

namespace ell 
{
    namespace utilities 
    {
        template <typename InputIteratorType, typename OutType, typename FuncType, int MaxTasks = 0>
        class ParallelTransformIterator 
        {
            public:
                ParallelTransformIterator(InputIteratorType& inIter, FuncType transformFunction);
                bool IsValid() const { return _currentIndex != _endIndex;}
                void Next();
                OutType Get() const;

            private:
                InputIteratorType& _inIter;
                FuncType _transformFunction;
                mutable std::vector<std::future<OutType>> _futures;
                mutable OutType _currentOutput;
                mutable bool _currentOutputValid;
                int _currentIndex = 0;
                int _endIndex = 0; 
        };

        template <typename InputIteratorType, typename FuncType>
        auto MakeParallelTransformIterator(InputIteratorType& inIterator, FuncType transformFunction) -> ParallelTransformIterator<InputIteratorType, decltype(transformFunction(inIterator.Get())), FuncType>;
    }
}

#pragma region implementation 

namespace ell 
{
    namespace utilities
    {
        template <typename InputIteratorType, typename OutType, typename FuncType, int MaxTasks>
        ParallelTransformIterator<InputIteratorType, OutType, FuncType, MaxTasks>::ParallelTransformIterator(InputIteratorType& inIter, FuncType transformFunction) : 
            _inIter(inIter),
            _transformFunction(transformFunction),
            _currentOutputValid(false),
            _currentIndex(0),
            _endIndex(-1)
        {
            int maxTasks = maxTasks == 0 ? std::thread::hardware_concurrency() : MaxTasks;
            if (maxTasks == 0)
            {
                maxTasks = DEFAULT_MAX_TASKS;
            }

            _futures.reserve(maxTasks);
            for (int index = 0; index < maxTasks; index++)
            {
                if (!_inIter.IsValid())
                {
                    break;
                }

                _futures.emplace_back(std::async(std::launch::async, _transformFunction, _inIter.Get()));
                _inIter.Next();
            }
        }

        template <typename InputIteratorType, typename OutType, typename FuncType, int MaxTasks>
        void ParallelTransformIterator<InputIteratorType, OutType, FuncType, MaxTasks>::Next()
        {
            if (!IsValid())
            {
                return;
            }
            _currentOutputValid = false;

            if (_inIter.IsValid())
            {
                _futures[_currentIndex] = std::async(std::launch::async, _transformFunction, _inIter.Get());
                _inIter.Next();
            }
            else 
            {
                if (_endIndex < 0)
                {
                    _endIndex = _currentIndex;
                }
            }
            _currentIndex = (_currentIndex + 1) % _futures.size();
        };

        template <typename InputIteratorType, typename OutType, typename FuncType, int MaxTasks>
        OutType ParallelTransformIterator<InputIteratorType, OutType, FuncType, MaxTasks>::Get() const 
        {
            if (!_currentOutputValid)
            {
                _currentOutput = _futures[_currentIndex].get();
                _currentOutputValid = true;
            }

            return _currentOutput;
        }

        template <typename InputIteratorType, typename FuncType>
        auto MakeParallelTransformIterator(InputIteratorType& inIterator, FuncType transformFunction) -> ParallelTransformIterator<InputIteratorType, decltype(transformFunction(inIterator.Get())), FuncType>
        {
            using OutType = decltype(transformFunction(inIterator.Get()));
            return ParallelTransformIterator<InputIteratorType, OutType, FuncType>(inIterator, transformFunction);
        }
    }
}

#pragma endregion implementation