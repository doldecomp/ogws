#include <nw4r/math.h>

namespace nw4r {
namespace math {
namespace {

struct ExpSample {
    f32 exp_val;   // at 0x0
    f32 exp_delta; // at 0x4
};

struct LogSample {
    f32 log_val;   // at 0x0
    f32 log_delta; // at 0x4
};

extern ExpSample sExpTbl[];
extern LogSample sLogTbl[];

f32 FExpLn2(f32 x) {
    f32 fidx = (16 / NW4R_MATH_LN_2) * (NW4R_MATH_LN_2 + x);
    u16 whole = F32ToU16(fidx);
    f32 frac = fidx - U16ToF32(whole);

    return sExpTbl[whole].exp_val + frac * sExpTbl[whole].exp_delta;
}

f32 FLog1_2(f32 x) {
    f32 fidx = 256.0f * (x - 1.0f);
    u16 whole = F32ToU16(fidx);
    f32 frac = fidx - U16ToF32(whole);

    return sLogTbl[whole].log_val + frac * sLogTbl[whole].log_delta;
}

} // namespace

namespace detail {

f32 FExp(f32 x) {
    s16 k = F32ToS16((1 / NW4R_MATH_LN_2) * x);
    f32 kf = S16ToF32(k);
    f32 expxn = FExpLn2(x - NW4R_MATH_LN_2 * kf);
    u32 expx = F32AsU32(expxn);

    return U32AsF32(((k << 23) + expx) & 0x7FFFFFFF);
}

f32 FLog(f32 x) {
    s32 exp = FGetExpPart(x);
    f32 xn = FGetMantPart(x);
    f32 kf = S16ToF32(exp);
    f32 logxn = FLog1_2(xn);

    return logxn + NW4R_MATH_LN_2 * kf;
}

} // namespace detail

f32 FrSqrt(register f32 x) {
    register f32 rsqrt;
    register f32 c_half = 0.5f, c_three = 3.0f;
    register f32 work0, work1;

    // clang-format off
    asm {
        // Estimate reciprocal square root
        frsqrte rsqrt, x
        
        // Refine estimate using Newton-Raphson method
        // y = 1 / sqrt(x)
        fmuls work0, rsqrt, rsqrt         // rsqrt^2
        fmuls work1, rsqrt, c_half        // rsqrt * 0.5
        fnmsubs work0, work0, x, c_three  // (3 - x * rsqrt^2)
        fmuls work1, work0, work1         // (3 - x * rsqrt^2) * (rsqrt * 0.5)
    }
    // clang-format on

    return work1;
}

namespace {

ExpSample sExpTbl[] = {
    // clang-format off
    {0.500000000f, 0.022136891f},
    {0.522136867f, 0.023116974f},
    {0.545253873f, 0.024140451f},
    {0.569394290f, 0.025209241f},
    {0.594603539f, 0.026325349f},
    {0.620928884f, 0.027490871f},
    {0.648419797f, 0.028707996f},
    {0.677127779f, 0.029979007f},
    {0.707106769f, 0.031306293f},
    {0.738413095f, 0.032692339f},
    {0.771105409f, 0.034139752f},
    {0.805245161f, 0.035651248f},
    {0.840896428f, 0.037229665f},
    {0.878126085f, 0.038877964f},
    {0.917004049f, 0.040599238f},
    {0.957603276f, 0.042396720f},
    {1.000000000f, 0.044273783f},
    {1.044273734f, 0.046233948f},
    {1.090507746f, 0.048280902f},
    {1.138788581f, 0.050418481f},
    {1.189207077f, 0.052650698f},
    {1.241857767f, 0.054981742f},
    {1.296839595f, 0.057415992f},
    {1.354255557f, 0.059958015f},
    {1.414213538f, 0.062612586f},
    {1.476826191f, 0.065384679f},
    {1.542210817f, 0.068279505f},
    {1.610490322f, 0.071302496f},
    {1.681792855f, 0.074459329f},
    {1.756252170f, 0.077755928f},
    {1.834008098f, 0.081198476f},
    {1.915206552f, 0.084793441f},
    {2.000000000f, 0.088547565f}
    // clang-format on
};

LogSample sLogTbl[] = {
    // clang-format off
    {0.000000000f, 0.003898640f},
    {0.003898640f, 0.003883500f},
    {0.007782140f, 0.003868477f},
    {0.011650617f, 0.003853569f},
    {0.015504187f, 0.003838776f},
    {0.019342963f, 0.003824096f},
    {0.023167059f, 0.003809528f},
    {0.026976587f, 0.003795071f},
    {0.030771660f, 0.003780723f},
    {0.034552380f, 0.003766483f},
    {0.038318865f, 0.003752350f},
    {0.042071216f, 0.003738322f},
    {0.045809537f, 0.003724399f},
    {0.049533933f, 0.003710579f},
    {0.053244516f, 0.003696862f},
    {0.056941375f, 0.003683245f},
    {0.060624622f, 0.003669729f},
    {0.064294353f, 0.003656311f},
    {0.067950659f, 0.003642991f},
    {0.071593650f, 0.003629768f},
    {0.075223424f, 0.003616640f},
    {0.078840062f, 0.003603608f},
    {0.082443669f, 0.003590668f},
    {0.086034335f, 0.003577821f},
    {0.089612156f, 0.003565066f},
    {0.093177222f, 0.003552402f},
    {0.096729629f, 0.003539827f},
    {0.100269452f, 0.003527341f},
    {0.103796795f, 0.003514942f},
    {0.107311733f, 0.003502631f},
    {0.110814363f, 0.003490405f},
    {0.114304774f, 0.003478264f},
    {0.117783032f, 0.003466208f},
    {0.121249244f, 0.003454235f},
    {0.124703482f, 0.003442344f},
    {0.128145829f, 0.003430535f},
    {0.131576359f, 0.003418807f},
    {0.134995162f, 0.003407158f},
    {0.138402328f, 0.003395589f},
    {0.141797915f, 0.003384098f},
    {0.145182014f, 0.003372684f},
    {0.148554698f, 0.003361348f},
    {0.151916042f, 0.003350087f},
    {0.155266136f, 0.003338901f},
    {0.158605024f, 0.003327790f},
    {0.161932826f, 0.003316753f},
    {0.165249571f, 0.003305788f},
    {0.168555364f, 0.003294896f},
    {0.171850264f, 0.003284075f},
    {0.175134331f, 0.003273325f},
    {0.178407654f, 0.003262646f},
    {0.181670308f, 0.003252035f},
    {0.184922338f, 0.003241494f},
    {0.188163832f, 0.003231021f},
    {0.191394851f, 0.003220615f},
    {0.194615468f, 0.003210276f},
    {0.197825745f, 0.003200003f},
    {0.201025739f, 0.003189795f},
    {0.204215541f, 0.003179653f},
    {0.207395196f, 0.003169575f},
    {0.210564762f, 0.003159560f},
    {0.213724330f, 0.003149609f},
    {0.216873944f, 0.003139720f},
    {0.220013663f, 0.003129893f},
    {0.223143548f, 0.003120127f},
    {0.226263672f, 0.003110422f},
    {0.229374096f, 0.003100778f},
    {0.232474878f, 0.003091193f},
    {0.235566065f, 0.003081667f},
    {0.238647744f, 0.003072199f},
    {0.241719931f, 0.003062790f},
    {0.244782731f, 0.003053437f},
    {0.247836158f, 0.003044142f},
    {0.250880301f, 0.003034904f},
    {0.253915220f, 0.003025721f},
    {0.256940931f, 0.003016594f},
    {0.259957522f, 0.003007521f},
    {0.262965053f, 0.002998503f},
    {0.265963554f, 0.002989539f},
    {0.268953085f, 0.002980628f},
    {0.271933705f, 0.002971770f},
    {0.274905473f, 0.002962965f},
    {0.277868450f, 0.002954212f},
    {0.280822664f, 0.002945510f},
    {0.283768177f, 0.002936860f},
    {0.286705047f, 0.002928260f},
    {0.289633304f, 0.002919710f},
    {0.292553008f, 0.002911210f},
    {0.295464218f, 0.002902760f},
    {0.298366964f, 0.002894358f},
    {0.301261336f, 0.002886005f},
    {0.304147333f, 0.002877700f},
    {0.307025045f, 0.002869442f},
    {0.309894472f, 0.002861232f},
    {0.312755704f, 0.002853069f},
    {0.315608770f, 0.002844952f},
    {0.318453729f, 0.002836881f},
    {0.321290612f, 0.002828856f},
    {0.324119478f, 0.002820876f},
    {0.326940358f, 0.002812941f},
    {0.329753280f, 0.002805051f},
    {0.332558334f, 0.002797205f},
    {0.335355550f, 0.002789402f},
    {0.338144958f, 0.002781643f},
    {0.340926588f, 0.002773927f},
    {0.343700528f, 0.002766253f},
    {0.346466780f, 0.002758622f},
    {0.349225402f, 0.002751033f},
    {0.351976424f, 0.002743486f},
    {0.354719907f, 0.002735980f},
    {0.357455879f, 0.002728515f},
    {0.360184401f, 0.002721090f},
    {0.362905502f, 0.002713706f},
    {0.365619212f, 0.002706362f},
    {0.368325561f, 0.002699057f},
    {0.371024609f, 0.002691792f},
    {0.373716414f, 0.002684565f},
    {0.376400977f, 0.002677378f},
    {0.379078358f, 0.002670229f},
    {0.381748587f, 0.002663117f},
    {0.384411693f, 0.002656044f},
    {0.387067735f, 0.002649008f},
    {0.389716744f, 0.002642009f},
    {0.392358750f, 0.002635048f},
    {0.394993812f, 0.002628122f},
    {0.397621930f, 0.002621233f},
    {0.400243163f, 0.002614381f},
    {0.402857542f, 0.002607563f},
    {0.405465096f, 0.002600782f},
    {0.408065885f, 0.002594035f},
    {0.410659939f, 0.002587324f},
    {0.413247257f, 0.002580647f},
    {0.415827900f, 0.002574004f},
    {0.418401897f, 0.002567396f},
    {0.420969307f, 0.002560821f},
    {0.423530102f, 0.002554280f},
    {0.426084399f, 0.002547772f},
    {0.428632170f, 0.002541297f},
    {0.431173474f, 0.002534856f},
    {0.433708310f, 0.002528446f},
    {0.436236769f, 0.002522069f},
    {0.438758850f, 0.002515725f},
    {0.441274554f, 0.002509412f},
    {0.443783969f, 0.002503130f},
    {0.446287096f, 0.002496880f},
    {0.448783994f, 0.002490661f},
    {0.451274633f, 0.002484473f},
    {0.453759104f, 0.002478316f},
    {0.456237435f, 0.002472189f},
    {0.458709627f, 0.002466092f},
    {0.461175710f, 0.002460026f},
    {0.463635743f, 0.002453989f},
    {0.466089725f, 0.002447982f},
    {0.468537718f, 0.002442004f},
    {0.470979720f, 0.002436055f},
    {0.473415762f, 0.002430135f},
    {0.475845903f, 0.002424244f},
    {0.478270143f, 0.002418381f},
    {0.480688542f, 0.002412546f},
    {0.483101070f, 0.002406740f},
    {0.485507816f, 0.002400962f},
    {0.487908781f, 0.002395211f},
    {0.490303993f, 0.002389487f},
    {0.492693484f, 0.002383791f},
    {0.495077252f, 0.002378122f},
    {0.497455388f, 0.002372480f},
    {0.499827862f, 0.002366865f},
    {0.502194762f, 0.002361276f},
    {0.504556000f, 0.002355714f},
    {0.506911695f, 0.002350177f},
    {0.509261906f, 0.002344667f},
    {0.511606574f, 0.002339182f},
    {0.513945758f, 0.002333723f},
    {0.516279459f, 0.002328290f},
    {0.518607736f, 0.002322881f},
    {0.520930648f, 0.002317498f},
    {0.523248136f, 0.002312140f},
    {0.525560260f, 0.002306806f},
    {0.527867079f, 0.002301497f},
    {0.530168593f, 0.002296212f},
    {0.532464802f, 0.002290952f},
    {0.534755766f, 0.002285715f},
    {0.537041485f, 0.002280503f},
    {0.539321959f, 0.002275314f},
    {0.541597307f, 0.002270149f},
    {0.543867409f, 0.002265007f},
    {0.546132445f, 0.002259888f},
    {0.548392355f, 0.002254792f},
    {0.550647140f, 0.002249720f},
    {0.552896857f, 0.002244670f},
    {0.555141509f, 0.002239643f},
    {0.557381153f, 0.002234638f},
    {0.559615791f, 0.002229655f},
    {0.561845422f, 0.002224695f},
    {0.564070165f, 0.002219757f},
    {0.566289902f, 0.002214840f},
    {0.568504751f, 0.002209946f},
    {0.570714653f, 0.002205073f},
    {0.572919726f, 0.002200221f},
    {0.575119972f, 0.002195391f},
    {0.577315390f, 0.002190581f},
    {0.579505920f, 0.002185793f},
    {0.581691742f, 0.002181026f},
    {0.583872795f, 0.002176279f},
    {0.586049020f, 0.002171554f},
    {0.588220596f, 0.002166848f},
    {0.590387464f, 0.002162163f},
    {0.592549622f, 0.002157498f},
    {0.594707131f, 0.002152853f},
    {0.596859932f, 0.002148229f},
    {0.599008203f, 0.002143624f},
    {0.601151824f, 0.002139038f},
    {0.603290856f, 0.002134473f},
    {0.605425298f, 0.002129926f},
    {0.607555270f, 0.002125399f},
    {0.609680653f, 0.002120892f},
    {0.611801565f, 0.002116403f},
    {0.613917947f, 0.002111933f},
    {0.616029859f, 0.002107482f},
    {0.618137360f, 0.002103050f},
    {0.620240390f, 0.002098637f},
    {0.622339070f, 0.002094242f},
    {0.624433279f, 0.002089865f},
    {0.626523137f, 0.002085506f},
    {0.628608644f, 0.002081166f},
    {0.630689800f, 0.002076844f},
    {0.632766664f, 0.002072540f},
    {0.634839237f, 0.002068253f},
    {0.636907458f, 0.002063984f},
    {0.638971448f, 0.002059733f},
    {0.641031206f, 0.002055499f},
    {0.643086672f, 0.002051283f},
    {0.645137966f, 0.002047084f},
    {0.647185028f, 0.002042902f},
    {0.649227977f, 0.002038737f},
    {0.651266694f, 0.002034589f},
    {0.653301299f, 0.002030458f},
    {0.655331731f, 0.002026343f},
    {0.657358050f, 0.002022245f},
    {0.659380317f, 0.002018164f},
    {0.661398470f, 0.002014099f},
    {0.663412571f, 0.002010051f},
    {0.665422618f, 0.002006019f},
    {0.667428672f, 0.002002003f},
    {0.669430673f, 0.001998003f},
    {0.671428680f, 0.001994019f},
    {0.673422694f, 0.001990050f},
    {0.675412714f, 0.001986098f},
    {0.677398801f, 0.001982161f},
    {0.679381013f, 0.001978240f},
    {0.681359231f, 0.001974334f},
    {0.683333576f, 0.001970444f},
    {0.685303986f, 0.001966569f},
    {0.687270582f, 0.001962709f},
    {0.689233303f, 0.001958864f},
    {0.691192150f, 0.001955035f},
    {0.693147182f, 0.001951220f}
    // clang-format on
};

} // namespace
} // namespace math
} // namespace nw4r
