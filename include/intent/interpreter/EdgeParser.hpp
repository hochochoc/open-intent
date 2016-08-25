/*
|---------------------------------------------------------|
|    ___                   ___       _             _      |
|   / _ \ _ __   ___ _ __ |_ _|_ __ | |_ ___ _ __ | |_    |
|  | | | | '_ \ / _ \ '_ \ | || '_ \| __/ _ \ '_ \| __|   |
|  | |_| | |_) |  __/ | | || || | | | ||  __/ | | | |_    |
|   \___/| .__/ \___|_| |_|___|_| |_|\__\___|_| |_|\__|   |
|        |_|                                              |
|                                                         |
|     - The users first...                                |
|                                                         |
|     Authors:                                            |
|        - Clement Michaud                                |
|        - Sergei Kireev                                  |
|                                                         |
|     Version: 1.0.0                                      |
|                                                         |
|---------------------------------------------------------|

The MIT License (MIT)
Copyright (c) 2016 - Clement Michaud, Sergei Kireev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef INTENT_EDGE_PARSER_HPP
#define INTENT_EDGE_PARSER_HPP

#include "intent/interpreter/Interpreter.hpp"
#include "intent/intent_story_service/IntentStoryModel.hpp"
#include "intent/intent_service/DictionaryModel.hpp"

namespace intent {

struct EdgeDefinition {
  IntentStoryModel::EdgeInfo edge;
  IntentStoryModel::VertexInfo source;
  IntentStoryModel::VertexInfo target;
  std::string replyTemplate;
};

class EdgeParser {
 public:
  EdgeParser(const DictionaryModel& dictionaryModel,
             int vertexCounter,
             int anonymousActionCounter,
             InterpreterFeedback& interpreterFeedback)
      : m_dictionaryModel(dictionaryModel),
        m_vertexCounter(vertexCounter),
        m_anonymousActionCounter(anonymousActionCounter),
        m_interpreterFeedback(interpreterFeedback) {}

  EdgeDefinition parse(const Scenario& scenario,
                       const InquiryToReply& inquiryToReply,
                       std::unique_ptr<std::string>& previousStateInScenario);

  std::unique_ptr<EdgeDefinition> parseFallback(
      const Scenario& scenario, const InquiryToReply& inquiryToReply,
      std::unique_ptr<std::string>& previousStateInScenario);

 private:
  const DictionaryModel& m_dictionaryModel;
  int m_vertexCounter;
  int m_anonymousActionCounter;
  InterpreterFeedback& m_interpreterFeedback;
};
}

#endif
