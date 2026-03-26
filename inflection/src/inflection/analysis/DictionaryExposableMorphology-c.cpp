#include <inflection/analysis/DictionaryExposableMorphology.h>
#include <inflection/analysis/DictionaryExposableMorphology.hpp>
#include <inflection/util/TypeConversionUtils.hpp>
#include <inflection/util/ULocale.hpp>
#include <inflection/util/Validate.hpp>
#include <inflection/npc.hpp>

using ::inflection::analysis::DictionaryExposableMorphology;
using ::inflection::util::TypeConversionUtils;

INFLECTION_CAPI int32_t dem_getWordGrammemeSets(
    const char* locale,
    const char16_t* word, int32_t wordLen,
    int64_t* results, int32_t resultsCapacity,
    UErrorCode* status)
{
    if (status != nullptr && U_SUCCESS(*status)) {
        try {
            inflection::util::Validate::notNull(locale);
            inflection::util::Validate::notNull(word);
            inflection::util::Validate::isTrue(resultsCapacity >= 0);

            ::std::u16string_view wordView = wordLen < 0
                ? ::std::u16string_view(word)
                : ::std::u16string_view(word, wordLen);

            DictionaryExposableMorphology morph{inflection::util::ULocale(locale)};
            auto grammemeSets = morph.getWordGrammemeSets(wordView);

            // Probe pass — just return count
            if (results == nullptr || resultsCapacity == 0) {
                return static_cast<int32_t>(grammemeSets.size());
            }

            // Fill results array
            int32_t count = static_cast<int32_t>(grammemeSets.size());
            int32_t toCopy = count < resultsCapacity ? count : resultsCapacity;
            
            for (int32_t i = 0; i < toCopy; ++i) {
                results[i] = grammemeSets[i];
            }

            return count;
        }
        catch (const ::std::exception& e) {
            TypeConversionUtils::convert(e, status);
        }
    }
    return -1;
}

INFLECTION_CAPI int32_t dem_getWordParadigmGrammemes(
    const char* locale,
    const char16_t* word, int32_t wordLen,
    int64_t* results, int32_t resultsCapacity,
    UErrorCode* status)
{
    if (status != nullptr && U_SUCCESS(*status)) {
        try {
            inflection::util::Validate::notNull(locale);
            inflection::util::Validate::notNull(word);
            inflection::util::Validate::isTrue(resultsCapacity >= 0);

            ::std::u16string_view wordView = wordLen < 0
                ? ::std::u16string_view(word)
                : ::std::u16string_view(word, wordLen);

            DictionaryExposableMorphology morph{inflection::util::ULocale(locale)};
            auto grammemeSets = morph.getWordParadigmGrammemes(wordView);

            // Probe pass — just return count
            if (results == nullptr || resultsCapacity == 0) {
                return static_cast<int32_t>(grammemeSets.size());
            }

            // Fill results array
            int32_t count = static_cast<int32_t>(grammemeSets.size());
            int32_t toCopy = count < resultsCapacity ? count : resultsCapacity;
            
            for (int32_t i = 0; i < toCopy; ++i) {
                results[i] = grammemeSets[i];
            }

            return count;
        }
        catch (const ::std::exception& e) {
            TypeConversionUtils::convert(e, status);
        }
    }
    return -1;
}
