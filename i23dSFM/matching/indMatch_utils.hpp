
// Copyright (c) 2012, 2013 Pierre MOULON.

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef I23DSFM_MATCHING_IND_MATCH_UTILS_H
#define I23DSFM_MATCHING_IND_MATCH_UTILS_H

#include "i23dSFM/matching/indMatch.hpp"
#include <map>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

namespace i23dSFM {
namespace matching {

/// Export vector of IndMatch to a stream
static bool PairedIndMatchToStream(
  const PairWiseMatches & map_indexedMatches,
  std::ostream & os)
{
  for (PairWiseMatches::const_iterator iter = map_indexedMatches.begin();
    iter != map_indexedMatches.end();
    ++iter)
  {
    const size_t I = iter->first.first;
    const size_t J = iter->first.second;
    const std::vector<IndMatch> & vec_matches = iter->second;
    os << I << " " << J << '\n' << vec_matches.size() << '\n';
    copy(vec_matches.begin(), vec_matches.end(),
         std::ostream_iterator<IndMatch>(os, "\n"));
  }
  return os.good();
}

/// Import vector of IndMatch from a file
static bool PairedIndMatchImport(
  const std::string & fileName,
  PairWiseMatches & map_indexedMatches)
{
  std::ifstream in(fileName.c_str());
  if (!in.is_open()) {
    std::cout << std::endl << "ERROR indexedMatchesUtils::import(...)" << std::endl
      << "with : " << fileName << std::endl;
    return false;
  }
  
  map_indexedMatches.clear();

  size_t I, J, number;
  while (in >> I >> J >> number)  {
    std::vector<IndMatch> matches(number);
    for (size_t i = 0; i < number; ++i) {
      in >> matches[i];
    }
    map_indexedMatches[std::make_pair(I,J)] = matches;
  }
  return true;
}

static void CopyIndMatches(const PairWiseMatches& src_indexedMatches,
                           PairWiseMatches& dst_indexedMatches)
{
  for (PairWiseMatches::const_iterator iter = src_indexedMatches.begin(); 
       iter != src_indexedMatches.end(); iter++) {
    size_t i = iter->first.first;
    size_t j = iter->first.second;
    const std::vector<IndMatch>& src_vec_matches = iter->second;
    std::vector<IndMatch> dst_vec_matches(src_vec_matches.begin(), src_vec_matches.end());
    dst_indexedMatches[std::make_pair(i, j)] = dst_vec_matches;
  }
}
}  // namespace matching
}  // namespace i23dSFM

#endif // #define I23DSFM_MATCHING_IND_MATCH_UTILS_H
